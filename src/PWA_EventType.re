type t('target, 'a);
external unsafe: string => t('target, 'a) = "%identity";

/*type t2('target, 'a, 'b);*/
/*external unsafe2: string => t2('target, 'a, 'b) = "%identity";*/
