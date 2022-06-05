// Copyright (c) 2022 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
extern crate ruf_tree;

use ruf_tree as tree;

pub mod ast
{
    #[derive(PartialEq)]
    pub struct Item<'text>
    {
	pub tag: Option<&'static str>,
	pub text: &'text str
    }
}
pub type AST<'text> = tree::Node<ast::Item<'text>>;

pub struct Context<'text, 'goal>
{
    pub at: &'text str,
    pub goal: &'goal dyn std::fmt::Display
}

pub struct ParseFailed<'text, 'goals, 'parser>
{
    pub cause: Box<dyn std::fmt::Display+'parser>,
    pub context: Vec< Context<'text, 'goals> >    // outermost is last
}

pub type ParseResult<'text, 'goals, 'parser> = std::result::Result<
	( crate::AST<'text>, &'text str ),
    ParseFailed<'text, 'goals, 'parser> >;

pub trait Parser
{
    fn parse_some_of<'text, 'goals, 'parser>(&'parser self, text: &'text str) ->
	ParseResult<'text, 'goals, 'parser>
      where 'text: 'parser, 'parser: 'goals;
}

pub type Ref<'parser> = std::sync::Arc<dyn Parser+'parser>;

pub mod parse
{
    pub struct Literal<'literal> {
	pub x: &'literal str
    }
    impl<'literal> std::fmt::Display for Literal<'literal>
    {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
	{
	    // REVISIT: need a rust-escape-string formatting function so that e.g.
	    // Literal{ x: "the \"big\" bird" } formats as:
	    // parse "the \"big\" bird"
	    write!(f, "\"{}\"", self.x)
	}
    }
    pub struct LiteralNotFound<'cause> {
	x: &'cause str,
	text: &'cause str
    }
    impl<'cause> LiteralNotFound<'cause>
    {
	fn new(x:&'cause str, text:&'cause str) -> Box<dyn std::fmt::Display+'cause>
	{
	    Box::new(LiteralNotFound::<'cause>{
		x: &x,
		text: &text
	    })
	}
    }
    
    impl<'cause> std::fmt::Display for LiteralNotFound<'cause> {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
	{
	    // REVISIT: quite hard to produce "fred..." does not start with "sal" properly
	    // due to unicode grapheme clusters, which below ignores
	    let n = self.x.chars().count();
	    if self.text.chars().count() <= n {
		return write!(f, "\"{}\" does not start with \"{}\"", self.text, self.x);
	    }
	    write!(f, "\"")?;
	    self.text.chars().take(n).try_for_each(|c| write!(f, "{}", c))?;
	    write!(f, "...\" does not start with \"{}\"", self.x)
	}
    }

    impl<'literal> crate::Parser for Literal<'literal>
    {
	fn parse_some_of<'text, 'goals, 'parser>(self: &'parser Self, text: &'text str) ->
	    crate::ParseResult<'text, 'goals, 'parser>
	where 'text: 'parser, 'parser: 'goals, 'literal: 'parser
	{
	    let result = {
		if text.starts_with(self.x) {
		    let (x, y) = text.split_at(self.x.len());
		    crate::ParseResult::<'text, 'goals, 'parser>::Ok(
			( crate::AST{ value: crate::ast::Item { tag: None, text: x },
				      children: vec!() }, y) )
		}
		else {
		    let goal = crate::Context{ goal: self, at: &text};
		    crate::ParseResult::<'text, 'goals, 'parser>::Err(
			crate::ParseFailed::<'text, 'goals, 'parser>{
			    context: vec!( goal ),
			    cause: LiteralNotFound::new(&self.x, &text)
			})
		}
	    };
	    match result {
		crate::ParseResult::Ok(x) => crate::ParseResult::Ok(x),
		crate::ParseResult::Err(mut e) => {
		    e.context.push( crate::Context::<'text, 'goals> { at: text, goal: self } );
		    crate::ParseResult::Err(e)
		}
	    }
	}
    }

    pub struct Tagged<'content> {
	pub tag: &'static str,
	pub content: crate::Ref<'content>
    }
    impl<'content> std::fmt::Display for Tagged<'content>
    {
	fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
	{
	    write!(f, "{}", self.tag)
	}
    }
    impl<'content> crate::Parser for Tagged<'content>
    {
	fn parse_some_of<'text, 'goals, 'parser>(self: &'parser Self, text: &'text str) ->
	    crate::ParseResult<'text, 'goals, 'parser>
	where 'text: 'parser, 'parser: 'goals, 'content: 'parser
	{
	    let result = self.content.parse_some_of(text);
	    match result {
		crate::ParseResult::Ok(x) => crate::ParseResult::Ok(
		    ( crate::AST{ value: crate::ast::Item{ tag: Some(self.tag), text: x.0.value.text },
				  children: vec!(x.0) },
		      x.1 )),
		crate::ParseResult::Err(mut e) => {
		    e.context.push( crate::Context::<'text, 'goals> { at: text, goal: self } );
		    crate::ParseResult::Err(e)
		}
	    }
	}
    }
}

pub fn literal(x: &'static str) -> Ref<'static>
{
    std::sync::Arc::new(parse::Literal{x: x})
}

pub fn tagged<'parser>(tag: &'static str, content: Ref<'parser>) -> Ref<'parser>
{
    std::sync::Arc::new(parse::Tagged{ tag: tag, content: content })
}
