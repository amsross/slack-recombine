open Types;

let attachment = attachment =>
  Json.Encode.(
    object_([
      ("color", string(attachment.color)),
      ("author_name", string(attachment.author_name)),
      ("author_link", string(attachment.author_link)),
      ("author_icon", string(attachment.author_icon)),
    ])
  );

let payload = payload =>
  Json.Encode.(
    object_([
      ("response_type", string(payload.response_type)),
      ("text", string(payload.text)),
      ("attachments", array(attachment, payload.attachments)),
    ])
  );
