type t('target, 'event);


external unsafe: string => t('a, 'b) = "%identity";