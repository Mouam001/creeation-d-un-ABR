#ifndef FonctionARN__hpp
#define FonctionARN__hpp

#include "FonctionABR.hpp"
#include <iostream>
using namespace std;

struct Noeud{

    int cle;
    char couleur;
    Noeud *filsGauche;
    Noeud *filsDroite;
    Noeud *pere;
};

 Noeud *NIL = new Noeud;


 
// Creation de l'arbre 
void creatUser(Noeud **racine){

    *racine = new Noeud;
    Noeud *ptr = *racine;
    string choix;
    char color;
  
     cout<<"Donner un noeud : ";
     cin>>ptr->cle;
     cout<<"Donner sa couleur(R or N) :";
     cin>>ptr->couleur;
     cout<<"fils Gauche (OUI or N) : ";
     cin>>choix;
   
    if (choix =="OUI"){
        creatUser(&(ptr->filsGauche));
        ptr->filsGauche->pere = *racine;
       
    }
      
    else   ptr->filsGauche = NIL;
    
  //cout<<endl;
     cout<<"fils Droite (OUI or N) : ";
     cin>>choix; 
   if(choix =="OUI") {
         creatUser(&(ptr->filsDroite));
         ptr->filsDroite->pere = *racine;
   }
   else  ptr->filsDroite = NIL;   
        
}

// Affichage de l'arbre par la methode prefixe
void afficherArbre(Noeud *racine) {

  if (racine != NIL ) {
   
    cout <<"Noeud : " <<racine->cle<<"  Color :"<<racine->couleur<<endl;
    afficherArbre(racine->filsGauche);
    afficherArbre(racine->filsDroite);
  }
 
}



//2)Fonction d'insertions et de supression d'un Noeud
/*2.1) Fonction de rotation à Gauche 
 Une fonction  rotation Gauche qui permet de transformer
  x en un fils gauche de son fils droite intial */

void rotation_Gauche(Noeud **racine, Noeud *noeudX){

    Noeud *noeudY = noeudX->filsDroite;
    noeudX->filsDroite = noeudY->filsGauche;

    if( noeudY->filsGauche != NULL){
        noeudY->filsGauche->pere = noeudX;
    }

    if(noeudX->pere ==NULL){
        *racine = noeudY;
    }
    else {

        if(noeudX->pere->filsGauche == noeudX){

            noeudX->pere->filsGauche =noeudY;
        }
      else {
         noeudX->pere->filsDroite = noeudY;
      }
    }
 // noeudY->pere = noeudX->pere;
  noeudY->filsGauche = noeudX;
  noeudX->pere = noeudY;
}

// Une fonction  rotation droite qui permet de transformer
//  x en un fils droite de son fils gauche intial 
void rotation_Droite(Noeud **racine, Noeud *noeudX){

    Noeud *noeudY = noeudX->filsGauche;
    noeudX->filsGauche = noeudY->filsDroite;

    if( noeudY->filsDroite != NULL){
        noeudY->filsDroite->pere = noeudX;
    }

    if(noeudX->pere ==NULL){
        *racine = noeudY;
    }
    else {

        if(noeudX->pere->filsDroite == noeudX){

            noeudX->pere->filsDroite =noeudY;
        }
      else {
         noeudX->pere->filsGauche = noeudY;
      }
    }
  noeudY->pere = noeudX->pere;
  noeudY->filsDroite = noeudX;
  noeudX->pere = noeudY;
}


//Affichage infixé pour tester les 2 rotations ci-dessus
void afficherInfixee(Noeud *racine){

      if (racine != NIL){

          afficherInfixee(racine->filsGauche);
          cout<<racine->cle<<" ; ";
          afficherInfixee(racine->filsDroite);
        
      }
}


// 2.2 les insertions dans un ARN 


void misAjourInsertionARN(Noeud **racine, Noeud *noeudInserer){

    Noeud *oncle;
  
    while( *racine != noeudInserer && noeudInserer->pere->couleur =='R' && noeudInserer->pere->pere != NULL) {
      if(noeudInserer->pere->pere->filsGauche == noeudInserer->pere){
        oncle = noeudInserer->pere->pere->filsDroite;
        if(oncle->couleur == 'R');
          
        else{
          
          if(noeudInserer->pere->filsDroite == noeudInserer){
            rotation_Gauche(racine, noeudInserer->pere);
          }
            
          else rotation_Droite(racine, noeudInserer->pere->pere);
        }
      }
        // le pere de noeudInserer est un fils droit de son grand pere 
      else {
        
        oncle = noeudInserer->pere->pere->filsGauche;
        if(oncle->couleur == 'R');
          
        else{
          
          if(noeudInserer->pere->filsGauche == noeudInserer){
            rotation_Droite(racine, noeudInserer->pere);
          }
            
          else {
            rotation_Gauche(racine, noeudInserer->pere->pere);
          }
        }
      }
  
    (*racine)->couleur = 'N';
}


void insertionARN(Noeud **racine, Noeud *noeudInserer){

    insertionABR(racine,noeudInserer);
    misAjourInsertionARN(racine,noeudInserer);
    
}

#endif

