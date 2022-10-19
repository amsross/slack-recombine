open Types;

let (<||) = (f, g, x) => f(g(x));
let (||>) = (f, g, x) => g(f(x));

let tail = xs => Array.sub(xs, 1, Array.length(xs) - 1);
let join = (s, xs) =>
  Array.fold_left(
    (a, b) => Js.String.length(a) > 0 ? a ++ s ++ b : b,
    "",
    tail(xs),
  );

let default = (opt, def) => Belt.Option.getWithDefault(opt, def);
let get = (dict, key) => Js.Dict.get(dict, key);
let getDefault = (def, key, dict) => dict->get(key)->default(def);
let filter = f =>
  Array.fold_left((xs, x) => f(x) ? Array.append(xs, [|x|]) : xs, [||]);
let gt = (x, y) => y > x;

let colors =
  Js.Dict.fromArray([|
    ("google", "#FFA500"),
    ("spotify", "#008000"),
    ("youtube", "#FF0000"),
    ("deezer", "#ADD8E6"),
    ("itunes", "#000000"),
    ("amazon", "#0000FF"),
  |]);

let buildAttachment: match_ => attachment =
  ({service, url, artwork}) => {
    color: service->getDefault("#FE4365", _, colors),
    author_name: service,
    author_link: url->default(""),
    author_icon: artwork->default(""),
  };

let buildAttachments: array(match_) => array(attachment) =
  match_ =>
    Array.map(buildAttachment, match_)
    |> filter(
         gt(0) <|| Js.String.length <|| (({author_link}) => author_link),
       );

let buildPayload: (Js.Dict.t(string), track) => payload =
  (parts, track) => {
    response_type: "in_channel",
    text:
      get(parts, "user_id")
      ->Belt.Option.map(user => "<@" ++ user ++ "> shared ")
      ->default("")
      ++ "*_<https://combine.fm/"
      ++ track.service
      ++ "/"
      ++ track.type_
      ++ "/"
      ++ track.externalId
      ++ "|"
      ++ track.artist.name
      ++ " - "
      ++ track.name
      ++ ">_*",
    attachments: buildAttachments(track.matches),
  };

let bodyToParts: string => Js.Dict.t(string) =
  Js.Global.decodeURIComponent
  ||> Js.String.split("&")
  ||> Array.map(Js.String.split("="))
  ||> Array.map(xs => (xs[0], join("=", xs)))
  ||> Js.Dict.fromArray;
