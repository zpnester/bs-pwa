type t('a);

external untyped: string => t(SW_Event.t) = "%identity";
external unsafe: string => t('a) = "%identity";