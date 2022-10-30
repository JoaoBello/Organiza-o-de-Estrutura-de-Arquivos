// Código para cortar o arquivo cep_ordenado.dat, já que o tamanho anteriormente era maior do que o possivel no GitHub.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, slice;

	f = fopen("cep_ordenado.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtd = posicao/sizeof(Endereco);
	slice = qtd/64;
	e = (Endereco*) malloc(slice*sizeof(Endereco));
	rewind(f);
	if(fread(e,sizeof(Endereco),slice,f) == slice)
	{
		printf("Lido = OK\n");
	}
	qsort(e,slice,sizeof(Endereco),compara);
	printf("Ordenado = OK\n");
	saida = fopen("cep_ordenado.dat","wb");
	fwrite(e,sizeof(Endereco),slice,saida);
	fclose(saida);
	printf("Escrito = OK\n");
	free(e);

	fclose(f);
}

