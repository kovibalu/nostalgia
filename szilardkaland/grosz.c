#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef	struct {
		char nev[21];
		int szint;
		int arany;
		int tp;
		int ero;
		int ugyesseg;
		int gyorsasag;
		int te;
		int ve;
		int sebzes;
		int hk;
		int skill1;
		int skill2;
		int skill3;
		int skillpont;
		int maxhp;
		int hp;
		int ujtargy[20];
		struct targy *aktiv;
		struct targy *targyfirst;
	}KARLAP;
typedef struct {
		int ero;
		int ugyesseg;
		int gyorsasag;
		int te;
		int ve;
		int sebzes;
		int hk;
		int maxhp;
		int hp;
	}HARCERTEK;
typedef struct ENEMYY {
		char nev[21];
		int maxhp;
		int hp;
		int sebzes;
		int te;
		int ve;
		int index;
		struct ENEMYY *next;
		struct ENEMYY *prev;}ENEMY;
typedef struct targy{
		int index;
		char nev[21];
		char tipus[11];
		int cel;
		int mennyiseg;
		int ar;
		int ero;
		int ugyesseg;
		int gyorsasag;
		int te;
		int ve;
		int sebzes;
		int hk;
		int maxhp;
		int hp;
		struct targy *prev;
		struct targy *next;
}TARGY;
typedef struct stargy{
		char index[4];
		char nev[21];
		char tipus[11];
		char cel[6];
		char mennyiseg[6];
		char ar[6];
		char ero[6];
		char ugyesseg[6];
		char gyorsasag[6];
		char te[6];
		char ve[6];
		char sebzes[6];
		char hk[6];
		char maxhp[6];
		char hp[6];

}STARGY;
typedef struct skillz{
		char skill[20];
}SKILLZ;
void kargen(KARLAP *karlap)
{
	int i;
	gets(karlap->nev);
	karlap->szint=1;
	karlap->tp=460;
	karlap->arany=10;
	karlap->ero=1;
	karlap->ugyesseg=1;
	karlap->gyorsasag=1;
	karlap->te=50;
	karlap->ve=100;
	karlap->sebzes=100;
	karlap->hk=10;
	karlap->skill1=0;
	karlap->skill2=0;
	karlap->skill3=0;
	karlap->skillpont=0;
	karlap->maxhp=200;
	karlap->hp=200;
	karlap->targyfirst=NULL;


for(i=0;i<20;i++)
{
	karlap->ujtargy[i]=0;
}



	/**/
	
	

	
	



}



void harertekkiirat(HARCERTEK *karlap)
{
	printf("***HARCERTEK********\n");
	printf("ero %d\n",karlap->ero);
	printf("ugyesseg %d\n",karlap->ugyesseg);
	printf("gyorsasag %d\n",karlap->gyorsasag);
	printf("tamado ertek %d\n",karlap->te);
	printf("vedo ertek %d\n",karlap->ve);
	printf("sebzes %d\n",karlap->sebzes);
	printf("harci kapacitas %d\n",karlap->hk);
	printf("maxhp %d\n",karlap->maxhp);
	printf("hp %d\n",karlap->hp);
	printf("********************\n");
}





void karlapkiirat(KARLAP *karlap)
{
	int i,j;
char skillz[7][50]={	"fegyverhasznalat ",
							"nehezvertviselet ",
							"pajzshasznalat ",
							"2kezes fegyverhasznalat ",
							"2fegyveres harc ",
							"mesterharc ",
							"harc tulerovel "};
/*ujtargyindex*/

for(i=0;i<20;i++)
{
	printf("ujtargyindex  %d\n",karlap->ujtargy[i]);
}


	printf("****KARAKTERLAP*****\n");
	printf("nev %s\n",karlap->nev);
	printf("szint: %d\n",karlap->szint);
	printf("arany: %d\n",karlap->arany);
	printf("tp: %d\n",karlap->tp);
	printf("ero %d\n",karlap->ero);
	printf("ugyesseg %d\n",karlap->ugyesseg);
	printf("gyorsasag %d\n",karlap->gyorsasag);
	printf("tamado ertek %d\n",karlap->te);
	printf("vedo ertek %d\n",karlap->ve);
	printf("sebzes %d\n",karlap->sebzes);
	printf("harci kapacitas %d\n",karlap->hk);
	/*printf("skill1 %d\n",karlap->skill1);
	printf("skill2 %d\n",karlap->skill2);
	printf("skill3 %d\n",karlap->skill3);*/
			for(i=0;i<7;i++)
			{
				if(i==karlap->skill2 || i==karlap->skill3 || i==
		karlap->skill1)
				{
					
					for(j=0;j<50;j++)
						{
						printf("%c",skillz[i][j]);
					}
					
					printf("\n");
				}
				
			
			}
							
					
	printf("skillpont %d\n",karlap->skillpont);
	printf("maxhp %d\n",karlap->maxhp);
	printf("hp %d\n",karlap->hp);
	printf("********************\n");
}


void szornykiirat(ENEMY *first)
{
	ENEMY *tmp;
	for(tmp=first;tmp;tmp=(tmp->next))
	{
		printf("***SZORNY******\n");
		printf("NEV: %13s \n",tmp->nev);	
		printf("index %12d\n",tmp->index);
		printf("maxhp %12d\n",tmp->maxhp);
		printf("hp %15d\n",tmp->hp);
		printf("te %15d\n",tmp->te);
		printf("ve %15d\n",tmp->ve);
		printf("sebzes %11d\n",tmp->sebzes);
		printf("******************\n");
		}
}

void egyszornykiirat(ENEMY *penemy)
{
	ENEMY *tmp;
	tmp=penemy;
		printf("***SZORNY******\n");
		printf("NEV: %13s \n",tmp->nev);	
		printf("index %12d\n",tmp->index);
		printf("maxhp %12d\n",tmp->maxhp);
		printf("hp %15d\n",tmp->hp);
		printf("te %15d\n",tmp->te);
		printf("ve %15d\n",tmp->ve);
		printf("sebzes %11d\n",tmp->sebzes);
		printf("******************\n");
	
}


void harcertekinicializalo(KARLAP *pkarlap, HARCERTEK *initharcertek,int *memte,int *memve)
{
initharcertek->ero=pkarlap->ero;
initharcertek->ugyesseg=pkarlap->ugyesseg;
initharcertek->gyorsasag=pkarlap->gyorsasag;
initharcertek->te=pkarlap->te;
initharcertek->ve=pkarlap->ve;
initharcertek->sebzes=pkarlap->sebzes;
initharcertek->hk=initharcertek->hk+pkarlap->hk;
initharcertek->maxhp=pkarlap->maxhp;
initharcertek->hp=pkarlap->hp;
if(*memte||*memve)
	{
	initharcertek->te=initharcertek->te+(*memte);
	initharcertek->ve=initharcertek->ve+(*memve);
	initharcertek->hk=initharcertek->hk-(*memte)-(*memve);
	}
}



ENEMY * celpont(ENEMY *,int);
int tamadas(HARCERTEK *pharce,KARLAP *pkarlap,ENEMY *ptarget,ENEMY **pptarget,ENEMY *first,int *pharcvege,int *pkiosztottsebzes)
{
	int tdb;
	int tmpsebzes=0;
	int nitarget;
	int frag=0;
	ENEMY *tmp;
/*tamadsz*/
	tdb=rand()%101;
	printf("*************TAMADAS!!!!!######\n");
	printf(" %d -t dobtal, osszesen %d+%d = %d vel tamadsz, [%d.ellenfel %s ve:] ellen\n",tdb,tdb,pharce->te,pharce->te+tdb,ptarget->index,ptarget->nev,ptarget->ve);
		if(pharce->te+tdb>ptarget->ve)
				{
					tmpsebzes=(rand()%(pharce->sebzes));
					*pkiosztottsebzes+=tmpsebzes;
					ptarget->hp=ptarget->hp-tmpsebzes;
					printf("                                   %d sebzest okoztal\n",tmpsebzes);
					if(ptarget->hp>0)
					{
					printf("                                   %d elete maradt\n",ptarget->hp);
					}
				}
		else
		{

	printf("Kivedtek a tamadasod\n");
		}
/*tamadnak*/
	printf("***********TAMADNAK**************\n");


	for(tmp=first;tmp;tmp=(tmp->next))
	{


					tdb=rand()%101;
					printf("%d -t dobott [ %d . ellenfel %s], osszesen %d+%d=%d vel tamadtott, %d vedesed ellen\n",tdb,tmp->index ,tmp->nev ,tdb,tmp->te,tmp->te+tdb,pkarlap->ve);
					if(ptarget->te+tdb>pharce->ve)
							{
								tmpsebzes=(rand()%(ptarget->sebzes));
								*pkiosztottsebzes+=tmpsebzes;
								pharce->hp=pharce->hp-tmpsebzes;
								pkarlap->hp=pkarlap->hp-tmpsebzes;
								
								printf("                                   %d sebzest kaptal\n",tmpsebzes);
								if(pkarlap->hp>0)
								{
								printf("                                   %d eleted maradt\n",pkarlap->hp);
								}
							}
					else
					{
						printf("kivedted [ %d . ellenfel %s] a tamadasat\n",tmp->index,tmp->nev);
					}
					if(pharce->hp<1)
					{
						printf("GAME OVER\n",tmp->index ,tmp->nev);
						exit(-1);
					}
	}
	/*frag+for vege*/

		printf("**************Vege a harci kornek,*********************\n");


	if(ptarget->hp<1)
	{
		printf("Legyozted az ellenfeled");
		frag=1;
	}
		return frag;
}
ENEMY * celpont(ENEMY *first,int celpontindex)
{
	ENEMY *tmpcelpont;
	for(tmpcelpont=first;tmpcelpont;tmpcelpont=(tmpcelpont->next))
	{
		if(tmpcelpont->index==celpontindex)
		{
			printf(" A CELPONTOD:\n");
			egyszornykiirat(tmpcelpont);
			return tmpcelpont;
		}
	}
	printf("ROSSZ CELPONT\n");
return NULL;
}
void targykiirat(TARGY *pfirsttargy)
{
	TARGY *temp;

	for(temp=pfirsttargy;temp;temp=temp->next)
	{
		printf("******targy******\n");
		printf("**********index :%10d\n",temp->index);
		printf("nev: %s",temp->nev);
		printf("tipus: %s",temp->tipus);
		printf("cel :%d\n",temp->cel);
		printf("mennyiseg :%d\n",temp->mennyiseg);
		printf("ar :%d\n",temp->ar);	
		printf("ero :%d\n",temp->ero);
		printf("ugyesseg :%d\n",temp->ugyesseg);
		printf("gyorsasag:%d\n",temp->gyorsasag);
		printf("te :%d\n",temp->te);
		printf("ve :%d\n",temp->ve);
		printf("sebzes :%d\n",temp->sebzes);
		printf("hk :%d\n",temp->hk);
		printf("maxhp :%d\n",temp->maxhp);
		printf("hp :%d\n",temp->hp);
		
	}

}

void gyuras(KARLAP *pkarlap)
{
	KARLAP kgyuras;
	int gyuras;
	int ok=1;
	for(ok=1;ok;)
	{
		kgyuras=*pkarlap;
		printf("     ero %d\n",pkarlap->ero);
		printf("ugyesseg %d\n",pkarlap->ugyesseg);
		printf("gyorsasag %d\n",pkarlap->gyorsasag);
		printf("Mire gyursz ? 1 ERO 2 UGYESSEG 3 GYORSASAG ?");
		scanf("%d",&gyuras);
		switch(gyuras)
		{
		case 1:
			kgyuras.ero+=1;
			break;
		case 2:
			kgyuras.ugyesseg+=1;
			break;
		case 3:
			kgyuras.gyorsasag+=1;
			break;
		default :
			printf("Igyal kevesebbet, akkor betalalsz 1-3 koze\n");
			break;
		
		}
		printf("ero %d\n",kgyuras.ero);
		printf("ugyesseg %d\n",kgyuras.ugyesseg);
		printf("gyorsasag %d\n",kgyuras.gyorsasag);
		printf("OK igy a szintlepes?1 IGEN 2 NEM\n");
		scanf("%d",&ok);
		if(ok==1)
		{
			ok=0;
			*pkarlap=kgyuras;
		}
	}
}

void skill(KARLAP *pkarlap)
{
	KARLAP kskill;
	int i,j;
	int ok;
	int skillvalaszto;
	int skillpont;
	char skillz[7][50]={	"fegyverhasznalat [alap]",
							"nehezvertviselet [ero 3]",
							"pajzshasznalat [ero 2 ugyesseg 2]",
							"2kezes fegyverhasznalat [ero 2]",
							"2fegyveres harc [ero 2 ugyesseg 3]",
							"mesterharc ",
							"harc tulerovel [gyorsasag 2]"};

	skillpont=pkarlap->skillpont;

for(;skillpont;skillpont=skillpont-1)
{
	printf("Van %d skillpontod\n",skillpont);

		for(ok=1;ok;)
		{
			kskill=*pkarlap;
			printf("Valassz skillt. 0 val kilepsz es tartalekolsz.\n");
			for(i=0;i<7;i++)
			{
				if(i!=pkarlap->skill2 && i!=pkarlap->skill3)
				{
					printf("%d ",i);
					for(j=0;j<50;j++)
						{
						printf("%c",skillz[i][j]);
						
							
						}
				}		
			printf("\n");
			}
			scanf("%d",&skillvalaszto);
						switch(skillvalaszto)
						{
						case 0:
							printf("Amit ma megtanulhatsz, azt elszalasztottad holnapra.");
						
							break;
					

						case 1:
							if(pkarlap->ero==3 && pkarlap->skill2!=2 && pkarlap->skill3!=2)

							{
								printf("Megtanultad a nehezvertviseletet");
								if(pkarlap->skill2==0)
								{
									kskill.skill2=1;
									pkarlap->skillpont=pkarlap->skillpont-1;
								}
								else
								{
									if(pkarlap->skill3==0)
									{
										kskill.skill3=1;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
										printf("HIBA MAR VAN 2 SKILLED");
									}
								}
							}
							else
							{
								ok=0;
							}
								break;
						case 2:
							if(pkarlap->ero>=2 && pkarlap->ugyesseg>=2 && pkarlap->skill2!=3 && pkarlap->skill3!=3)

							{
								printf("Megtanultad a pajzshasznalatot");
								if(pkarlap->skill2==0)
								{
									kskill.skill2=2;
									pkarlap->skillpont=pkarlap->skillpont-1;
								}
								else
								{
									if(pkarlap->skill3==0)
									{
										kskill.skill3=2;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
										printf("HIBA MAR VAN 2 SKILLED");
									}
								}
							}
							else
							{
								ok=0;
							}
								break;
					case 3:
							if(pkarlap->ero==2 && pkarlap->skill2!=4 && pkarlap->skill3!=4)

							{
								printf("Megtanultad a 2kezes fegyverhasznalatot");
								if(pkarlap->skill2==0)
								{
									kskill.skill2=3;
									pkarlap->skillpont=pkarlap->skillpont-1;
								}
								else
								{
									if(pkarlap->skill3==0)
									{
										kskill.skill3=3;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
										printf("HIBA MAR VAN 2 SKILLED");
									}
								}
							}
							else
							{
								ok=0;
							}
								break;
					case 4:
						if(pkarlap->ero>=2 && pkarlap->ugyesseg==3 && pkarlap->skill2!=5 && pkarlap->skill3!=5)

							{
									printf("Megtanultad a 2kezes harcot");
									if(pkarlap->skill2==0)
									{
										kskill.skill2=4;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
											if(pkarlap->skill3==0)
											{
												kskill.skill3=4;
												pkarlap->skillpont=pkarlap->skillpont-1;
											}
											else
											{
												printf("HIBA MAR VAN 2 SKILLED");
											}
										}
								

								}
						else
							{
								ok=0;
							}
								break;
					case 5:
							if(pkarlap->skill2!=6 && pkarlap->skill3!=6)

							{
								printf("MEGTANULTAD A MESTERHARCOT");
								if(pkarlap->skill2==0)
								{
									kskill.skill2=5;
									pkarlap->skillpont=pkarlap->skillpont-1;
								}
								else
								{
									if(pkarlap->skill3==0)
									{
										kskill.skill3=5;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
										printf("HIBA MAR VAN 2 SKILLED");
									}
								}
							}
							else
							{
								ok=0;
							}
								break;
					case 7:
							if(pkarlap->gyorsasag==2 && pkarlap->skill2!=7 && pkarlap->skill3!=7)

							{
								printf("Megtanultal tulerovel harcolni");
								if(pkarlap->skill2==0)
								{
									kskill.skill2=6;
									pkarlap->skillpont=pkarlap->skillpont-1;
								}
								else
								{
									if(pkarlap->skill3==0)
									{
										kskill.skill3=6;
										pkarlap->skillpont=pkarlap->skillpont-1;
									}
									else
									{
										printf("HIBA MAR VAN 2 SKILLED");
									}
								}
							}
							else
							{
								ok=0;
							}
								break;
					default:
							printf("ROSSZ SZAM");
							break;
							}
			if(ok)
			{

				printf("OK igy a szintlepes?1 IGEN 2 NEM\n");
				scanf("%d",&ok);
				if(ok==1)
				{
					ok=0;
					*pkarlap=kskill;
									}
			}
			else
			{
				printf("Nemtudod megtanulni azt a skillt valassz masikat vagy tartalekolj\n");
				ok=1;
			}
		}
	}

}

void szintlepes(KARLAP *pkarlap)
{

	KARLAP kskill;
	int i,j;
	int ok;
	int skillvalaszto;
	int skillpont;
	char skillz[7][50]={	"fegyverhasznalat [alap]",
							"nehezvertviselet [ero 3]",
							"pajzshasznalat [ero 2 ugyesseg 2]",
							"2kezes fegyverhasznalat [ero 2]",
							"2fegyveres harc [ero 2 ugyesseg 3]",
							"mesterharc ",
							"harc tulerovel [gyorsasag 2]"};

	/*szintlepo ertekek*/
	pkarlap->tp=pkarlap->tp-150;
	pkarlap->szint+=1;
	if(pkarlap->szint>2)
	{
	pkarlap->skillpont+=1;
	}
	skillpont=pkarlap->skillpont;
	
	

	printf("A kovetkezo kepzettsegeket vannak:\n");
	for(i=0;i<7;i++)
	{
		if(i!=pkarlap->skill2 && i!=pkarlap->skill3)
		{
			printf("%d ",i+1);
			for(j=0;j<50;j++)
				{
				printf("%c",skillz[i][j]);
				
					
				}
		}		
	printf("\n");
	}
	printf("Most jol gondold meg merre fejlodsz!\n");
	gyuras(pkarlap);
	skill(pkarlap);
	
}

void targyhasznalat(KARLAP *pkarlap,HARCERTEK *pharcertek,ENEMY *target)
{
	/*cel 1 tamado -1 magad 0 nem harci */
TARGY *ptargy;
int index;
int flag=1;
int van=0;
ptargy=pkarlap->targyfirst;
targykiirat(pkarlap->targyfirst);
printf("Melyik targyat hasznalod? -1 gyel visszalepsz\n");
scanf("%d",&index);
if(index!=-1)
{
		while(flag)
		{
			if(ptargy->index==index)
			{
				flag=0;
				van=1;
			}
			else
			{
					if(ptargy->next==NULL)
						{
							flag=0;
						}
					else
						{
						ptargy=ptargy->next;
						}
			}
		
			

		}
	if(van && ptargy->cel>0)
		{
		
		pharcertek->ero+=ptargy->ero;
		pharcertek->ugyesseg+=ptargy->ugyesseg;
		pharcertek->gyorsasag+=ptargy->gyorsasag;
		pharcertek->te+=ptargy->te;
		pharcertek->ve+=ptargy->ve;
		pharcertek->sebzes+=ptargy->sebzes;
		pharcertek->hk+=ptargy->hk;
		pharcertek->maxhp+=ptargy->maxhp;
		pharcertek->hp+=ptargy->hp;
	/**/	
		ptargy->mennyiseg--;
		if(ptargy->mennyiseg<=0)
		{
			if(ptargy==pkarlap->targyfirst)
			{
				if(ptargy->next==NULL)
				{
					pkarlap->targyfirst=NULL;
				}
				else
				{
					pkarlap->targyfirst=pkarlap->targyfirst->next;
					pkarlap->targyfirst->prev=NULL;
					}
			
			}
			else
			{
				if(ptargy->next==NULL)
				{
					ptargy->prev->next=NULL;
				}
				if(ptargy->next!=NULL && ptargy->prev!=NULL)
				{
				ptargy->next->prev=ptargy->prev;
				ptargy->prev->next=ptargy->next;
				}
			}
		free(ptargy);
		}
	/**/
	}
	if(van && ptargy->cel==0)
	{
		/* passziv*/
		
	}
	if(van && ptargy->cel==2)
	{
		target->te-=ptargy->te;
		target->ve-=ptargy->ve;
		target->sebzes-=ptargy->sebzes;
		target->maxhp-=ptargy->maxhp;
		target->hp-=ptargy->hp;
	}
}
}
void targykonvert(STARGY *stargy,TARGY *targy)
{
int i,t=1,sum=0;
strcpy(targy->nev,stargy->nev);
strcpy(targy->tipus,stargy->tipus);


for(i=0;(stargy->cel)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->cel)[i]!='\n';i++)
{
	sum+=(((stargy->cel)[i])-'0')*t;
	t=t/10;
	
}
targy->cel=sum;
sum=0;
t=1;

for(i=0;(stargy->mennyiseg)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->mennyiseg)[i]!='\n';i++)
{
	sum+=(((stargy->mennyiseg)[i])-'0')*t;
	t=t/10;
	
}
targy->mennyiseg=sum;
sum=0;
t=1;


for(i=0;(stargy->ar)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->ar)[i]!='\n';i++)
{
	sum+=(((stargy->ar)[i])-'0')*t;
	t=t/10;
	
}
targy->ar=sum;
sum=0;
t=1;


for(i=0;(stargy->ero)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->ero)[i]!='\n';i++)
{
	sum+=(((stargy->ero)[i])-'0')*t;
	t=t/10;
	
}
targy->ero=sum;
sum=0;
t=1;


for(i=0;(stargy->ugyesseg)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->ugyesseg)[i]!='\n';i++)
{
	sum+=(((stargy->ugyesseg)[i])-'0')*t;
	t=t/10;
	
}
targy->ugyesseg=sum;
sum=0;
t=1;


for(i=0;(stargy->gyorsasag)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->gyorsasag)[i]!='\n';i++)
{
	sum+=(((stargy->gyorsasag)[i])-'0')*t;
	t=t/10;
	
}
targy->gyorsasag=sum;
sum=0;
t=1;


for(i=0;(stargy->te)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->te)[i]!='\n';i++)
{
	sum+=(((stargy->te)[i])-'0')*t;
	t=t/10;
	
}
targy->te=sum;
sum=0;
t=1;


for(i=0;(stargy->ve)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->ve)[i]!='\n';i++)
{
	sum+=(((stargy->ve)[i])-'0')*t;
	t=t/10;
	
}
targy->ve=sum;
sum=0;
t=1;


for(i=0;(stargy->sebzes)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->sebzes)[i]!='\n';i++)
{
	sum+=(((stargy->sebzes)[i])-'0')*t;
	t=t/10;
	
}
targy->sebzes=sum;
sum=0;
t=1;


for(i=0;(stargy->hk)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->hk)[i]!='\n';i++)
{
	sum+=(((stargy->hk)[i])-'0')*t;
	t=t/10;
	
}
targy->hk=sum;
sum=0;
t=1;


for(i=0;(stargy->maxhp)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->maxhp)[i]!='\n';i++)
{
	sum+=(((stargy->maxhp)[i])-'0')*t;
	t=t/10;
	
}
targy->maxhp=sum;
sum=0;
t=1;


for(i=0;(stargy->hp)[i]!='\n';i++)
{
	t*=10;
	
	
}
t=t/10;
for(i=0;(stargy->hp)[i]!='\n';i++)
{
	sum+=(((stargy->hp)[i])-'0')*t;
	t=t/10;
	
}
targy->hp=sum;
sum=0;
t=1;

}
void beolvas(TARGY *ptargy,int kindex)
{
	FILE *f;
	/*static TARGY dzsin;*/
	static STARGY lampas;
	char temp[99];/* a filet soronkent ezzel allitom*/
	char memo1[99];
	char memo2[99];

	int flag=1;
	int hatvany;
	
	int i;
	char stringindex[99];
	/*TARGY *ptargy;*/
	STARGY *pstargy;
	pstargy=&lampas;
	/*ptargy=&dzsin;*/


	
	



	/***kindex stringe konvertalasa***/
	if(kindex==0 || kindex==1)
	{
		stringindex[0]=kindex+'0';
		stringindex[1]='\n';
		stringindex[2]='\0';
	}
	else
	{

		for(hatvany=1;hatvany<kindex;hatvany*=10);
		hatvany=hatvany/10;
		for(i=0;hatvany;i++,hatvany=hatvany/10)
		{
			stringindex[i]='0'+kindex/hatvany;
		}
		stringindex[i]='\n';
		stringindex[i+1]='\0';
	}
	/*konverzio vege*/

			
	f=fopen("targy.txt","r");

	do
	{
		fgets(memo1,99,f);
		fgets(memo2,99,f);
		if(!strcmp(memo1,"index\n"))
		{
			if(!strcmp(memo2,stringindex))
			{
				flag=0;
			}
		}

	}
	while(flag);

	fgets(temp,99,f);
	fgets(lampas.nev,21,f);
	fgets(temp,99,f);
	fgets(lampas.tipus,21,f);
	fgets(temp,99,f);
	fgets(lampas.cel,21,f);
	fgets(temp,99,f);
	fgets(lampas.mennyiseg,21,f);
	fgets(temp,99,f);
	fgets(lampas.ar,21,f);
	fgets(temp,99,f);
	fgets(lampas.ero,21,f);
	fgets(temp,99,f);
	fgets(lampas.ugyesseg,21,f);
	fgets(temp,99,f);
	fgets(lampas.gyorsasag,21,f);
	fgets(temp,99,f);

	fgets(lampas.te,21,f);
	fgets(temp,99,f);
	fgets(lampas.ve,21,f);
	fgets(temp,99,f);

	fgets(lampas.sebzes,21,f);
	fgets(temp,99,f);
	fgets(lampas.hk,21,f);
	fgets(temp,99,f);
	fgets(lampas.maxhp,21,f);
	fgets(temp,99,f);
	fgets(lampas.hp,21,f);


	fclose;



		targykonvert(pstargy,ptargy);
		
/*kiiratas*/
		/*

		printf("index\n%d\n",dzsin.index);
		printf("nev\n%s",dzsin.nev);
		printf("tipus\n%s",dzsin.tipus);
		printf("cel\n%d\n",dzsin.cel);
		printf("mennyiseg\n%d\n",dzsin.mennyiseg);
		printf("ar\n%d\n",dzsin.ar);	
		printf("ero\n%d\n",dzsin.ero);
		printf("ugyesseg\n%d\n",dzsin.ugyesseg);
		printf("gyorsasag\n%d\n",dzsin.gyorsasag);
		printf("te\n%d\n",dzsin.te);
		printf("ve\n%d\n",dzsin.ve);
		printf("sebzes\n%d\n",dzsin.sebzes);
		printf("hk\n%d\n",dzsin.hk);
		printf("maxhp\n%d\n",dzsin.maxhp);
		printf("hp\n%d\n",dzsin.hp);*/


		ptargy->index=kindex;





}
int harc(KARLAP *pkarlap, int nenemy)
{
int loot;
int harcvege,cselekves=0;
int *pharcvege=&harcvege;
int hkte,hkve;
ENEMY *szfirst;
ENEMY *tmp;
ENEMY *prev;
ENEMY *next;
ENEMY *target=NULL;
ENEMY **pptargett=&target;
HARCERTEK harcertek;
HARCERTEK *pharcertek;
int i=0;
int itarget;
int itargy=0;
int frag=0;
int memote=0;
int memove=0;
int *pmemote;
int *pmemove;
int autoelosztas;
int kiosztottsebzes=0;
int *pkiosztottsebzes;
pharcertek=&harcertek;
/*pharcertek->hk=0;/*hk 0 ra inicializalasa*/
szfirst=tmp=prev=next=NULL;
pmemote=&memote;
pmemove=&memove;
pkiosztottsebzes=&kiosztottsebzes;
loot=nenemy;


/*szornygen*/
for(i=0;i<nenemy;i++)
	{
		tmp=(ENEMY*)malloc(sizeof(ENEMY));
				if(tmp==NULL)
				{
					printf("memoria foglalasi hiba!!!!");
				}
				else
				{
				}
		if(szfirst==NULL)
			{
				szfirst=tmp;
				szfirst->prev=NULL;
			}
			else
			{
			prev->next=tmp;
			tmp->prev=prev;
			}
			prev=tmp;
			tmp->next=NULL;
			tmp->index=i;
			/*inicializalas kesobb majd filebol...*/
			strcpy(tmp->nev, "ORK");
			tmp->maxhp=120;
			tmp->hp=120;
			tmp->te=60;
			tmp->ve=100;
			tmp->sebzes=12;

		}
szornykiirat(szfirst);

/*harc*/
if(nenemy>1)
{
printf("Kezdodik a harc!! Ki legyen a celpontod?\n");
			szornykiirat(szfirst);
			scanf("%d",&itarget);
			target=celpont(szfirst,itarget);
}
else
{
	printf("Kezdodik a harc\n!!");
			target=celpont(szfirst,0);
}

/*inicializalas*/
pharcertek->hk=0;/*harcertek hk 0 ra allitasa csata elott*/
harcertekinicializalo(pkarlap,pharcertek,pmemote,pmemove);
/**/
	
for(harcvege=nenemy;harcvege && (pkarlap->hp)>0;)
{
/*celpontvizsgalat*/
	while(!target)
	{
		printf("Ki legyen a celpontod?\n");
			szornykiirat(szfirst);
			scanf("%d",&itarget);
			target=celpont(szfirst,itarget);
	}


		
		printf("Mit cselekszel?\n1 TAMADSZ \n2 karakterkiiratas \n3 szornykiiratas\n4 harcertekkiritasa \n");
		printf("5 Celpontvalasztasz \n6Celpontkiiratas \n7 HARCIKAPACITAS \n8TARGYHASZNALAT \n9 Elfutsz\n");
		scanf("%d",&cselekves);
		switch(cselekves)
		{
		case 1: printf("TAMADAS ...\n");
			frag=0;
			frag=tamadas(pharcertek,pkarlap,target,pptargett,szfirst,pharcvege,pkiosztottsebzes);
			harcvege=harcvege-frag;
			/*poiter allitas+torles*/
			if(frag)
			{
				if(harcvege)
				{/*szelen*/
					if(target->prev==NULL)
					{
						target->next->prev=NULL;
						szfirst=target->next;
					}
					if(target->next==NULL)
					{
						target->prev->next=NULL;
						
					}
					/*kozepen*/
					if(target->prev!=NULL)
					{
						if(target->next!=NULL)
						{
							target->next->prev=target->prev;
							target->prev->next=target->next;
						}
					}
					free(target);
					printf("Ki legyen a celpontod?\n");
					szornykiirat(szfirst);
					scanf("%d",&itarget);
					target=celpont(szfirst,itarget);
				}
			}
			harcertekinicializalo(pkarlap,pharcertek,pmemote,pmemove);
			break;
		case 2: printf("Karakterkiiratas ...\n");
			karlapkiirat(pkarlap);
			break;
		case 3: printf("Szornykiiratas ...\n");
			szornykiirat(szfirst);
			break;
		case 4: printf("harcertekkiritas ...\n");
			harertekkiirat(pharcertek);
			break;
		case 5: printf("Ki legyen a celpontod?\n");
			szornykiirat(szfirst);
			scanf("%d",&itarget);
			target=celpont(szfirst,itarget);
			break;			
		case 6: printf("******CELPONT******\n");
			egyszornykiirat(target);
			break;
		case 7: printf("HK ELOSZTAS\n");
			if(pharcertek->hk==0)
			{
				printf("0 harcerteked van, nincs elosztas.\n");
				break;
			}
			/*elosztas*/
			do
			{
			printf("Ennyi harci kapacitasod van:%d\n",pharcertek->hk);
			printf("Mennyit raksz a TE re ?\n");
			scanf("%d",&hkte);
			printf("Mennyit raksz a VE re ?\n");
			scanf("%d",&hkve);
			if(hkte+hkve>pharcertek->hk)
			{
				printf("ROSSZ ELOSZTAS");
			}
			}
			while(hkte+hkve>pharcertek->hk);
			/*beallitas*/
			pharcertek->te=hkte+pharcertek->te;
			pharcertek->ve=hkve+pharcertek->ve;
			pharcertek->hk=(pharcertek->hk)-(hkte+hkve);
			/*if((hkte+hkve)<=pkarlap->hk)
			{
				printf("Legyen auto elosztas?1Igen 0Nem\n");
				scanf("%d",&autoelosztas);
				if(autoelosztas)
				{
					memote=hkte;
					memove=hkve;
				}
				else
				{
					memote=0;
					memove=0;
				}
			}
			*/
			break;	
		case 8: 
			
			if(pkarlap->targyfirst!=NULL)
			{
			printf("***Targyhasznalat***\n");
			targyhasznalat(pkarlap,pharcertek,target);
			}
			else
			{
				printf("Nincs targyad\n");
			}
						break;
		case 9: printf("ELFUTSZ\n");
			harcvege=0;
			break;
		default:
			printf(" rossz szam\n");
			break;
		}

	}
printf("Ebben a csataban %d sebzest frageltek, amiert %d TP t kapsz\n",kiosztottsebzes,(kiosztottsebzes/10));
pkarlap->tp+=kiosztottsebzes/10;
return loot;
}


TARGY * keres(TARGY *pfirst,char nev[21])
{
	TARGY *kereso;
	TARGY *preturn=NULL;
	/*printf("KERESES\n");*/
	for(kereso=pfirst;kereso!=NULL;kereso=kereso->next)
	{
		/*printf("index %d VAN %s\n",kereso->index,kereso->nev);*/
		if(!strcmp(nev,kereso->nev))
		{
			/*printf("VAN EGYEZES");*/
			preturn=kereso;

		}

	}
	return preturn;
}
TARGY * utolsoptr(TARGY *pfirst)
{
	TARGY *pfuto;
	for(pfuto=pfirst;pfuto->next!=NULL;pfuto=pfuto->next);
return pfuto;
}

void bolt(KARLAP *pkarlap)
{
TARGY *pfuto;
TARGY *previ=NULL;
TARGY *first=NULL;
TARGY *vanmar=NULL;
TARGY *delmemo;
int kindx;
int mennyi;
int i;
int buyflag=1;
int buyflag2=1;
int buy;
int ujtargyindex=0;
int keszlet;
previ=NULL;
mennyi=rand()%6+1;/*mennyi cucc legyen a boltban*/
keszlet=mennyi;



kindx=rand()%3+1;
first=(TARGY *)malloc(sizeof(TARGY));
beolvas(first,kindx);
first->prev=NULL;
first->next=NULL;
previ=first;







for(i=1;i<=mennyi;i++)
{
	kindx=rand()%3+1;/*milyen cuccok+1 hogy 0 ne legyen*/
	pfuto=(TARGY *)malloc(sizeof(TARGY));
	beolvas(pfuto,kindx);
	pfuto->next=NULL;
	pfuto->prev=previ;
	/*pfuto->index=i;*/
	
			if((vanmar=keres(first,pfuto->nev))!=NULL)
			{
			vanmar->mennyiseg=vanmar->mennyiseg+1;
			previ->next=NULL;
			free(pfuto);
			}
			else
				{
				previ->next=pfuto;
				previ=pfuto;
				}
			
	}
/*vasarlas*/
do
{
	buyflag2=1;
	targykiirat(first);
printf("Mit szeretnel venni?\n");
scanf("%d",&buy);
for(pfuto=first;buyflag2;pfuto=pfuto->next)
{
	if(pfuto->index==buy)
	{
		buyflag2=0;
		if(pfuto->ar<=pkarlap->arany)
		{
			printf("MEGVETTED A (%s) TARGYAT\n",pfuto->nev);
			pfuto->mennyiseg=pfuto->mennyiseg-1;
			pkarlap->ujtargy[ujtargyindex]=pfuto->index;
			ujtargyindex++;
										
			keszlet=keszlet-1;
										
							
			
	
			if(pfuto->mennyiseg<=0 && keszlet>0)
			{
				if(pfuto==first)
				{
					pfuto->next->prev=NULL;
					first=pfuto->next;
					free(pfuto);
				}
				else
				{

					if(pfuto->next==NULL)
					{
						pfuto->prev->next=NULL;
						free(pfuto);
					}
					else
					{

						if(pfuto->next!=NULL && pfuto->prev!=NULL)
						{
							pfuto->prev->next=pfuto->next;
							pfuto->next->prev=pfuto->prev;
							free(pfuto);
						}
					}
				}
			}
		}
		else
		{
			printf("Nincs eleg penzed!\n");
		}
	}
	
	if(keszlet>0)
				{
	if(pfuto->next==NULL)
	{
		printf("Nincs ilyen termek.\n");
		buyflag2=0;
	}
				}
}

if(keszlet>0)
{
printf("Akarsz vmi mast?1 igen 0 nem\n");
scanf("%d",&buyflag);
}
else
{
	buyflag=0;
}


}

while(buyflag);


/*torles
for(pfuto=first;pfuto!=NULL;)
{
	delmemo=pfuto->next;
	pfuto->prev=pfuto->next=NULL;
	
free(pfuto);
pfuto=delmemo;
}

*/

}
void main(void)
{
	
	KARLAP karakterlap,*pkarakterlap;
	int endofgame,whattodo=0;
	int darab;
	int i;
	int mallocflag=0;
	TARGY *previ;
	TARGY *pfuto;
	TARGY *vanmar=NULL;
	static TARGY taktiv[4];
	
	
	/*hatizsak elso targy*/
	/*static TARGY hatizsak;*/



	printf("IT KNIGHT 2008\n");
	pkarakterlap=NULL;
	/*strcpy(hatizsak.nev,"hatizsak");
	strcpy(hatizsak.tipus,"hatizsak");
	hatizsak.ar=0;
	hatizsak.cel=-1;
	hatizsak.ero=hatizsak.ugyesseg=hatizsak.gyorsasag=hatizsak.te=hatizsak.ve=hatizsak.sebzes=hatizsak.hk=hatizsak.maxhp=hatizsak.hp;
	hatizsak.te=hatizsak.ve=666;
	hatizsak.prev=NULL;
	hatizsak.next=NULL;*/
	

		
	
	for(endofgame=1;endofgame;)
	{
		printf("Mit szeretnel csinalni?\n1 karaktergeneralas \n2 karakterkiiratas \n3 HARCOLNI \n4 Targylista \n5 Szintlepes \n6 SKILL elosztas \n7Bolt  \n8 game over\n");
		scanf("%d",&whattodo);
		

		switch(whattodo)
		{
		case 1: printf("Karaktergeneralas ...\n");
			/*pointer inicializalas*/		
			pkarakterlap=&karakterlap;
			kargen(pkarakterlap);
			karakterlap.aktiv=taktiv;
			/*hatizsak+arany targylistaba adas*/
			/*karakterlap.targyfirst=&hatizsak;		*/				
			break;
		case 2: printf("Karakterkiiratas ...\n");
			if(pkarakterlap)
				{
				karlapkiirat(pkarakterlap);
				}
			else
			{
				printf("Hozz letre karaktert\n");
			}
			break;
		case 3:			
			if(pkarakterlap)
			{
			printf("Hany ellenfellel akarsz megkuzdeni?");
			scanf("%d",&darab);
			harc(pkarakterlap,darab);
				/*targyak mallocolasa*/
				karlapkiirat(pkarakterlap);
				for(i=0;i<20;i++)
				{
					if(karakterlap.ujtargy[i]>0)
					{
						if(karakterlap.targyfirst==NULL)
						{
						karakterlap.targyfirst=(TARGY *)malloc(sizeof(TARGY));
						beolvas(karakterlap.targyfirst,karakterlap.ujtargy[i]);
						karakterlap.targyfirst->prev=NULL;
						karakterlap.targyfirst->next=NULL;
						/*karakterlap.targyfirst->mennyiseg-=1;*/
						previ=karakterlap.targyfirst;
						karakterlap.ujtargy[i]=0;
						break;
						}
					}
				}	
				for(i=0;i<20;i++)
				{
							if(karakterlap.ujtargy[i]>0)
							{
							pfuto=(TARGY *)malloc(sizeof(TARGY));
							beolvas(pfuto,karakterlap.ujtargy[i]);
							karakterlap.ujtargy[i]=0;
							pfuto->next=NULL;
							pfuto->prev=previ;								
										if((vanmar=keres(karakterlap.targyfirst,pfuto->nev))!=NULL)
										{
										vanmar->mennyiseg=vanmar->mennyiseg+1;
										previ->next=NULL;
										free(pfuto);
										}
										else
										{
										previ->next=pfuto;
										previ=pfuto;
										}
									
							}
				}
	

/*malloc vege*/




			}
			else
			{
				printf("Hozz letre karaktert\n");
			}		
			break;
		case 4:


			if(pkarakterlap)
			{
			printf("TARGYLISTA\n");
			targykiirat(karakterlap.targyfirst);
			
			}
			else
			{
				printf("Hozz letre karaktert\n");
			}		
			break;
		case 5: printf("Szintlepes\n");
			if(karakterlap.tp>=150)
			{
				printf("Eleg ver szarad a lelkeden, hogy nyugodtan szintet lephess.\n");
				szintlepes(pkarakterlap);
			}
			else
			{
				printf("Meg nem FRAGGeltel eleget, hogy szintet lephes, menj es rottalj!!!\n");
			}

			break;

		case 6:printf("ELMESZ tanulni, a felev soran eloszor...");
			skill(pkarakterlap);
			break;
		case 7:			
if(pkarakterlap)
{
				printf("Bolt\n");
				bolt(pkarakterlap);
				/*targyak mallocolasa*/
				karlapkiirat(pkarakterlap);
				for(i=0;i<20;i++)
				{
					if(karakterlap.ujtargy[i]>0)
					{
						if(karakterlap.targyfirst==NULL)
						{
						karakterlap.targyfirst=(TARGY *)malloc(sizeof(TARGY));
						beolvas(karakterlap.targyfirst,karakterlap.ujtargy[i]);
						karakterlap.targyfirst->prev=NULL;
						karakterlap.targyfirst->next=NULL;
						/*karakterlap.targyfirst->mennyiseg-=1;*/
						previ=karakterlap.targyfirst;
						karakterlap.ujtargy[i]=0;
						break;
						}
					}
				}	
				for(i=0;i<20;i++)
				{
							if(karakterlap.ujtargy[i]>0)
							{
							pfuto=(TARGY *)malloc(sizeof(TARGY));
							beolvas(pfuto,karakterlap.ujtargy[i]);
							karakterlap.ujtargy[i]=0;
							pfuto->next=NULL;
							pfuto->prev=previ;								
										if((vanmar=keres(karakterlap.targyfirst,pfuto->nev))!=NULL)
										{
										vanmar->mennyiseg=vanmar->mennyiseg+1;
										previ->next=NULL;
										free(pfuto);
										}
										else
										{
										previ->next=pfuto;
										previ=pfuto;
										}
									
							}
				}
	

/*malloc vege*/
}
			else
			{
				printf("Hozz letre karaktert\n");
			}
			break;
		case 8: printf("game over\n");
			endofgame=0;
		break;
		default:
			printf(" rossz szam\n");
			break;
		}

	}

}