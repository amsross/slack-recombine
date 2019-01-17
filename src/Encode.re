open Types;

let attachment = attachment =>
  Json.Encode.(
    object_([
      ("color", string(attachment->colorGet)),
      ("author_name", string(attachment->author_nameGet)),
      ("author_link", string(attachment->author_linkGet)),
      ("author_icon", string(attachment->author_iconGet)),
    ])
  );

let payload = payload =>
  Json.Encode.(
    object_([
      ("response_type", string(payload->response_typeGet)),
      ("text", string(payload->textGet)),
      ("attachments", array(attachment, payload->attachmentsGet)),
    ])
  );
