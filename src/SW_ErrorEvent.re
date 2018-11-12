include SW_Event;

open SW_Types;

[@bs.get] external message_: t => Js.Nullable.t(string) = "message";
[@bs.get] external filename_: t => Js.Nullable.t(string) = "filename ";
[@bs.get] external lineno_: t => Js.Nullable.t(int) = "lineno";
[@bs.get] external colno_: t => Js.Nullable.t(int) = "colno";
[@bs.get] external error_: t => Js.Nullable.t(any) = "error";

let message = (self: t) => self->message_->Js.Nullable.toOption;
let filename = (self: t) => self->filename_->Js.Nullable.toOption;
let lineno = (self: t) => self->lineno_->Js.Nullable.toOption;
let colno = (self: t) => self->colno_->Js.Nullable.toOption;
let error = (self: t) => self->error_->Js.Nullable.toOption;