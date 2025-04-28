# Analisador-de-DHT

Projeto de Smart Meter desenvolvido usando esp32 e compoenentes para analisar QEE em instalações elétricas residenciais.
Foco em analise de conteudo harmonico e DHT, usando técnicas de processamento digital de sinais, MAF, Fourier e outras.
Foi utilizado softwares como Arduino, PSIM, Excel com data streammer.
O circuito foi estrategicamente montado avaliando e tratando sinais da rede eletrica com circuito condicionador usando a base de testes arduino.
O Circuito final ( é aplicado no esp32, utilizando o circuito condicionador e sensores como PZEM-04T.

O Codigo final(codigo completo) do circuito apresenta travamento de analogread pra garantir exatidão da coleta de dados, aviso de limpeza de memoria, entre outras melhorias.


Considerações para projetos futuros:
- Aplicar Prodist mod 5 para padronizar a coleta de dados a serem aplicadas segundo o regimento do Prodist mod 8 e as normas IEC.
