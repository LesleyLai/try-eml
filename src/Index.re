module Editor {
  open Ace;

  ace
    ->configGet
    ->set("basePath", "/ace-builds/src-noconflict");

  let editor = ace-> edit("editor");
  editor-> setTheme("ace/theme/twilight");
}


Css.(
  global("html, body", [margin(px(0)), height(pct(100.))])
);

ReactDOMRe.renderToElementWithId(<Repl />, "repl");
