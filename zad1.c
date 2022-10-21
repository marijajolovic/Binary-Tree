#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct stablo
{
	int x;
	struct stablo *levi;
	struct stablo *desni;
};

void dodaj(struct stablo **koren, int x)
{
	if (!*koren)
	{
		*koren = (struct stablo*) malloc (sizeof(struct stablo));
		(*koren)->x = x;
		(*koren)->levi = (*koren)->desni = NULL;
		
		return;
	}
	if (x < (*koren)->x) dodaj(&((*koren)->levi), x);
	else dodaj(&((*koren)->desni), x);
}

void ispis(struct stablo *koren)
{
	if (!koren) return;
	
	ispis(koren->levi);
	printf("%d ", koren->x);
	ispis(koren->desni);
}

int maksimum(struct stablo *koren)
{
 	while(koren->desni)
 	{
 		koren=koren->desni;
 	}
 	return koren->x;
}

int zbir(struct stablo *koren)
{
	if (!koren) return 0;
	return koren->x + zbir(koren->levi) + zbir(koren->desni);
}

int dubina(struct stablo *koren)
{
	if (!koren) return 0;
	return 1 + fmax(dubina(koren->levi), dubina(koren->desni));
}

int nadjiX(struct stablo *glava,int x, int nivo)
{
	if (!glava) return -1;
	if (glava->x == x) return nivo;
	if (x < glava->x) nadjiX(glava->levi,x, nivo+1);
	else nadjiX(glava->desni, x, nivo+1);
}


int nadjiXINivo(struct stablo *glava, int x)
{
	return nadjiX(glava,x, 0);
}

int main()
{
	struct stablo *glava = NULL;
	
	int x;
	
	while(scanf("%d", &x) && x)
	{
		dodaj(&glava, x);
	}
	
	ispis(glava);
	printf("\n");
	printf("Maksimum: %d\n", maksimum(glava));
	printf("Zbir svih clanova: %d\n", zbir(glava));
	printf("Dubina: %d\n", dubina(glava));
	
	x=100;
	printf("Broj %d se nalazi na %d. nivou.\n", x, nadjiXINivo(glava,x));
}
