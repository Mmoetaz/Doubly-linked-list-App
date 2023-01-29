/*MohamedMoetaz Boughalmi
Doubly linked list Application
Application:Liste doublement chainee
Language:french
L'insertion va etre au debut de la liste ==>affichage->(LIFO), Mais on a le choix car la liste est doublement chainee on peut
ajouter une autre procedure pour l'affichage FIFO(ou bien l'insertion).
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1) definition de type Liste_Adherent
typedef struct {
    int code;
    char NomTour[35];
}Tournoi;
typedef struct {
    int NumLic;
    char NomAd[35];
    char PreAd[35];
    int nb;
    Tournoi tab[10];
}adherent;
typedef struct c{
    adherent adhr;
    struct c *next ;
    struct c *prev;
}Liste_Adherent;
typedef Liste_Adherent *liste;
//Creation d'un adherent.
adherent creer(){
    adherent a;
    int i;
    printf("\t\t\t**Nouvel Adherent! ^.^ **\n");
    printf("\t\t\tNumero:");
    scanf("\t\t\t%d",&a.NumLic);
    printf("\t\t\tNom:");
    scanf("%s",a.NomAd);
    printf("\t\t\tPrenom:");
    scanf("%s",a.PreAd);
    do{
        printf("\t\t\t\tNombre de TOURNOIS:");
        scanf("%d",&a.nb);
    }while(a.nb<1||a.nb>10);
    for(i=0;i<a.nb;i++){
    printf("\t\t\t\t-codeTour:");
    scanf("%d",&a.tab[i].code);
    printf("\t\t\t\t-NomTour:");
    scanf("%s",a.tab[i].NomTour);
    }
    return a;
}


//Initialiser Liste a vide.
void initialiser_liste(liste *l){
    *l=NULL;
}

//2)Procedure ajouter debut.
void ajouter_debut(adherent adr,liste *l){
    liste p=(Liste_Adherent*)malloc(sizeof(Liste_Adherent));
    p->adhr=adr;
    p->prev=NULL;
    if(*l==NULL){
        p->next=NULL;
    }else
    {
        p->next=*l;
        (*l)->prev=p;
    }
    *l=p;
}


//afficher la liste
void afficher(liste l){
    liste p;
    int i;
    p=l;
    printf("\t\t\t\t\tAdherents:\n");
    if(l==NULL){
        printf("La liste est vide!\n");
    }else{
        while(p!=NULL){
            printf("______________________\n");
            printf("Numero adherent:%d \n",p->adhr.NumLic);
            printf("NOM:%s\n",p->adhr.NomAd);
            printf("Prenom:%s\n",p->adhr.PreAd);
            for(i=0;i<p->adhr.nb;i++){
                printf("Tournoi %d:\t\t",i+1);
                printf("Code Tournoi:%d\t|\t",p->adhr.tab[i].code);
                printf("Nom Tournoi:%s\n",p->adhr.tab[i].NomTour);
            }
            printf("______________________\n");
            p=p->next;
        }
    }

}
//3)nombre des joueurs participants dans le tournoi: nom.
int nb_joueur(char nom[],liste l){
    liste p=l;
    int i;
    int n=0;
    while(p!=NULL){
        for(i=0;i<p->adhr.nb;i++){
            if(strcmp(nom,p->adhr.tab[i].NomTour)==0){
                n++;
                break;/*->si un adhérent choisit deux fois le même tournoi,
                        on utilise 'break' pour compter le nom du tournoi une seule fois pour chaque adherent.
                        ('break' to count the name of tournament once for each adherent)*/
            }
        }
        p=p->next;
    }
    return n;

}
//4)Procedure supprimer .
void supprimer(liste *l,int num){
    liste p = *l;
    //tester tant que p est differente de NULL.(p is not null)
    while (p != NULL) {
        //tester l'egalite des valeurs.(Values are equal)
        if (p->adhr.NumLic == num) {
            //p existe dans le milieu de la chaine.(p exists in the middle of the list)
            //on faire la liaison entre noeud precedente de p et noeud suivant.(we link the previous node of p to the next node of p).
            if (p->prev != NULL) {
                p->prev->next = p->next;
            }
            //faire le meme travail, liaison du noeud suivant avec noeud precedent.we link the next node of p to the previous node of p.
            if (p->next != NULL) {
                p->next->prev = p->prev;
            }
            //si p est a la tete de la liste -> p=l.l prend p->next (ou l->next) et on libere p.(if p is in the head of the list we move l to the next node)
            if (p == *l) {
                *l = p->next;
            }
            //vider (p).
            free(p);
            break;
        }
        p = p->next;
    }

}



//liberer les noeuds de la liste.
void freelist(liste *l){
    liste p;
    while(*l!=NULL){
        p=*l;
        *l=(*l)->next;
        free(p);
    }
}

//Fonction Main
 main(){
    printf("\t\t\t\t\t\tWELCOME\n");
    printf("\t\t\t\t\t----------------------\n");
    int count,num;
    liste l;
    adherent a;
    char nom[40];
    initialiser_liste(&l);
    printf("Cliquez '1' pour ajouter un nouvel adherent.\nCliquez '2' pour afficher la liste des adherents.\n");
    printf("Cliquez '3' pour avoir le nbre de joueurs dans un Tournoi specifique.\n");
    printf("Cliquez '4' pour supprimer un adherent.\n");
    printf("Cliquez '0' pour quitter. \n");
    do{
        printf("Choix:");
        scanf("%d",&count);
        if(count==1){
            a=creer();
            ajouter_debut(a,&l);
        }
        if(count==2){
            afficher(l);
        }
        if(count==3){
            printf("Nom Tournoi a chercher:");
            scanf("%s",nom);
            printf("le nombre de joueurs qui ont participe a cette tournois ==> %d\n",nb_joueur(nom,l));

        }
        if(count==4){
            printf("Numero License a supprimer:");
            scanf("%d",&num);
            supprimer(&l,num);
        }
        if(count==0){
            printf("Merci!\nFin.\n\n\n\n");
        }
    }while(count!=0);
    freelist(&l);
 }
