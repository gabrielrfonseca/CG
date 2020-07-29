
### ATIVIDADE 3 - IMPLEMENTAÇÃO DO PIPELINE GRÁFICO

#### GABRIEL ALCÂNTARA 
#### SABRINA SILVA 



##### INTRODUÇÃO
Todo objeto (em computação gráfica), seja ele bidimensional ou tridimensional, possui um eixo de coordenadas que mostra onde é a origem do objeto e como ele está orientado. Para este trabalho utilizaremos objetos 3d, ou seja, para descrever nossos objetos precisamos utilizar uma base ortonormal X, Y, Z.

Então, para posicionar objetos no universo, é necessário realizar transformações pois nem sempre queremos o objeto na origem do universo, que é o que aconteceria caso este não sofresse transformações e tiver sido modelado na origem.
Pode-se aplicar a um objeto transformações como  Escala, Translação  Projeção Perspectiva e Posição da Câmera. 


##### Compilação e Execução do Código Base para teste do funcionamento


### Transformações

#### Escala
A Transformação de Escala altera as proporções do objeto, podendo ser Isotrópica, onde não há alteração do aspecto do objeto (a escala para todas as coordenadas do objeto é igual), ou Anisotrópica, onde a escala para pelo menos uma das coordenadas é diferente.

A primeira alteração feita foi na matriz Model, e teve como objetivo mudar a escala dos triângulos que aparecem na tela. Aplicando as alterações especificadas pelo professor o resultado da transformação foi: 

![](Imagens/translation.png)


Os valores aplicados a matriz model para obter o respectivo resultado foram:

![](Imagens/translation.png)

#### Translação

A matriz de translação vai simplesmente transladar os pontos que forem transformados pela matriz:

![](Imagens/translation.png)

#### Projeção Perspectiva
![](Imagens/translation.png)


#### Posição da Câmera
![](Imagens/translation.png)
![](Imagens/translation.png)
![](Imagens/translation.png)
![](Imagens/translation.png)
#### Transformações Livres
![](Imagens/translation.png)
![](Imagens/translation.png)
![](Imagens/translation.png)
![](Imagens/translation.png)


#### Desafios encontrados 


#### Referências


