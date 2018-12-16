type session;

type editor;
[@bs.send] external setTheme: (editor, string) => unit = "setTheme";

type config;
[@bs.send] external set: (config, string, string) => unit = "set";

[@bs.deriving abstract]
type ace = {
  config: config
};
[@bs.send] external edit: (ace, string) => editor = "edit";

[@bs.module "ace-builds/src-noconflict/ace.js"] external ace: ace = "default";
