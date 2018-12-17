type t('target, 'event);

external untyped: string => t('a, SW_Event.t) = "%identity";
external unsafe: string => t('a, 'b) = "%identity";