# Trabalho Final - Laboratório de programação.

<h3>Código feito em C e modularizado recebe duas imagens, uma original e outra modificada, e retorna por meio de um arquivo uma matriz de coocorrência.</h3>

<h3>Descrevendo o código:</h3>
<br>
<p>-> Tratamento de dados:</p>
<li>Recebe e verifica o recebimento da quantização por linha de comando.</li>
<li>Abre o diretório que contém as imagens com a funções da biblioteca dirent.h.</li>
<li>Download da <a href = "https://www.dropbox.com/s/4vl9cjntaehn5b9/images.zip?dl=0">pasta de imagens</a></li>
<li>Seta o nome do arquivo de saída -> "SCM-Qtz " + quantização digitada pelo usuário e verifica se o arquivo foi aberto.</li>
<li>Verifica se o diretório está aberto, se estiver entra em um for que termina o laço quando (dir = readdir(d)) != NULL, sendo o dir um ponteiro para uma estrutura dirent, ou seja, o laço acaba quando todos os arquivos do diretório forem percorridos.</li>
<li>Esse laço pula de um em um, pois o programa foi feito da seguinte forma: ao ler o nome do arquivo, verifica-se o seu título, se tiver o "mean", que significa que é uma imagem modificada, não original, é pulado um laço (continue), se não tiver, entra-se em um outro laço.</li>
<li>Nesse outro laço, é instaciada outra estrutura do mesmo tipo da "dir" citado acima. Porém, sua função é achar a imagem mean relacionada a imagem que está no ponteiro "dir". Após achar, essas imagens são setadas em strings e interligadas para uso no código.</li>
<br>
<p>-> Explicando a função SCM:</p>
<li>A função calculaSCM recebe como parâmentro um ponteiro de inteiro, dois ponteiro da estrutura pgm, a quantização, um ponteiro do tipo FILE, e um caractere.</li>
<li>Todos os ponteiros são alocados.</li>
<li>Os dados das matrizes são alocado em ponteiros após passarem pela quantização.</li>
<li>No ponteiro SCM, é setado zero em todas as posições e possui o tamanho quantização*quantização.</li>
<li>Em um for dentro do outro, é colocado a seguinte expressão a qual é a parte principal da função: <br> ---------> <strong>*(scm + *(matrizA + i * coluna + x) * quant + *(matrizB + i * coluna + x)) += 1;</strong></li>
<li>É usado um código calcula-matriz-ex para facilitar o entendimento da implementação utilizada acima.</li>
<li>Algumas verificações são feitas: a soma de todos os valores da matriz SCM é igual a linha*coluna da matriz analizada, as dimensões da matriz SCM é quantização x quantização.</li>
