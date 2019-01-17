open Types;
open Helpers;

let rec fetch = (url: string, i: int) =>
  Js.Promise.(
    Axios.postData("https://combine.fm/search", {"url": url})
    |> then_(p =>
         i == 0 ? fetch(url, i + 1) : resolve(Decode.track(p##data))
       )
  );

let main = (parts: Js.Dict.t(string)): Js.Promise.t(string) => {
  let url = getDefault("", "text", parts);

  Js.Promise.(
    fetch(url, 0)
    |> then_(
         resolve
         <|| Js.Json.stringify
         <|| Encode.payload
         <|| buildPayload(parts),
       )
  );
};

let app: handler =
  (evt, _ctx, callback) => {
    let parts = evt |> bodyGet |> Js.Global.decodeURIComponent |> bodyToParts;

    Js.Promise.(
      main(parts)
      |> then_(body => resolve({statusCode: 200, body}))
      |> catch(err => {
           Js.Console.error(err);
           resolve({statusCode: 500, body: Js.String.make(err)});
         })
      |> then_(response => {
           callback(None, response);
           resolve(response);
         })
    );
  };
