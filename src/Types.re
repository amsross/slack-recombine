type artist = {name: string};

type match_ = {
  type_: option(string),
  service: string,
  url: option(string),
  artwork: option(string),
};

type track = {
  type_: string,
  name: string,
  service: string,
  externalId: string,
  artist,
  matches: array(match_),
};

type attachment = {
  color: string,
  author_name: string,
  author_link: string,
  author_icon: string,
};

type payload = {
  text: string,
  response_type: string,
  attachments: array(attachment),
};

type buffer;
[@bs.send] external toString: buffer => string = "toString";

type response = {
  statusCode: int,
  body: string,
};

[@bs.deriving abstract]
type event = {body: string};
type context;
type callback = (option(Js.Promise.error), response) => unit;
type handler = (event, context, callback) => Js.Promise.t(response);
