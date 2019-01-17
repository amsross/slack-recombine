open Types;

let artist = (artist: Js.Json.t): artist =>
  Json.Decode.{name: field("name", string, artist)};

let match_ = (match_: Js.Json.t): match_ =>
  Json.Decode.{
    type_: optional(field("type", string), match_),
    service: field("service", string, match_),
    url: optional(field("streamUrl", string), match_),
    artwork: optional(field("artworkSmall", string), match_),
  };

let track = (track: Js.Json.t): track =>
  Json.Decode.{
    type_: field("type", string, track),
    name: field("name", string, track),
    service: field("service", string, track),
    externalId: field("externalId", string, track),
    artist: field("artist", artist, track),
    matches: field("matches", array(match_), track),
  };
