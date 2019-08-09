type t('target, 'a);
external unsafe: string => t('target, 'a) = "%identity";