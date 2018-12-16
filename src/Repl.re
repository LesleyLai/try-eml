type record = {
  command: string,
  response: string,
}

let record_to_elem(record: record) = {
  <div>
  <p> {ReasonReact.string("> " ++ record.command)} </p>
  {
    Array.map(line => <p> {ReasonReact.string("  " ++ line)} </p>, Js.String.split("\n", record.response))
    -> ReasonReact.array
  }
  </div>
}

type state = {
  history: list(record),
  inputTest: string
};

type action =
    | Enter
    | InputText(string)

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

module Styles = {
  /*Open the Css module, so we can access the style properties below without prefixing them with Css.*/
  open Css;
  open Calc;

  let input = style([
    fontFamily("monospace"),
    fontSize(px(16)),
    color(hex("FFFFFF")),
    backgroundColor(transparent),
    borderStyle(none),
    width(pct(100.) - px(40)),
    focus([
      outlineStyle(none),
    ]),
  ]);
}

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {history: [], inputTest: ""},

  reducer: (action, state) => {
    switch (action) {
      | InputText(newTest) => {
        ReasonReact.Update({...state, inputTest: newTest})
      }
      | Enter => {
        let jsInterpret: string => string = [%bs.raw {|
          function(s) {
            const interpret = cwrap('interpret',
                           'null', // return type
                           ['string']);
            return Pointer_stringify(interpret(s));
          }
        |}];
        let request = state.inputTest;
        let response = jsInterpret(request);
        ReasonReact.Update({inputTest: "",
                            history: [{command: request, response: response}, ...state.history]});
      }
    }
  },

  render: self => {
    <>
      <p>
        {ReasonReact.string("Embedded ML v0.0.0, copyright Lesley Lai")}
      </p>

      (
          List.map(record_to_elem, self.state.history)
          -> List.rev
          -> Array.of_list
          -> ReasonReact.array
      )

      <span>
          {ReasonReact.string("> ")}
      </span>
        
      <input
      autoFocus=true
      value=self.state.inputTest
      className=Styles.input
      onKeyDown=(event => switch(ReactEvent.Keyboard.which(event)) {
        | 13 => self.send(Enter)
        | _ => ()
      })
      onChange=(event => {
        self.send(InputText(ReactEvent.Form.target(event)##value));
      })
      />
    </>;
    },
};
