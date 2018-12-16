let editor = Ace.ace->Ace.edit("editor");
editor->Ace.setTheme("ace/theme/twilight");

Css.(
  global("html, body", [margin(px(0)), height(pct(100.))])
);

ReactDOMRe.renderToElementWithId(<Repl />, "repl");
