#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Plat {
    char* nom;
    char* categorie;
    float prix;
} Plat;

typedef struct ElementPlat {
    Plat plat;
    struct ElementPlat* suivant;
    struct ElementPlat* precedent;
} ElementPlat;

typedef struct Menu {
    char* nom;
    ElementPlat* plats;
} Menu;

typedef struct ElementMenu {
    Menu menu;
    struct ElementMenu* suivant;
    struct ElementMenu* precedent;
} ElementMenu;

/* Search Operations */
void afficherPlatParCategorie(Menu M, char* categorie) {
    ElementPlat* current = M.plats;
    while(current != NULL) {
        if(strcmp(current->plat.categorie, categorie) == 0) {
            printf("%s\n", current->plat.nom);
        }
        current = current->suivant;
    }
}

ElementMenu* chercherParNom(ElementMenu* Em, char* nom) {
    ElementMenu* current = Em;
    while(current != NULL) {
        if(strcmp(current->menu.nom, nom) == 0) {
            return current;
        }
        current = current->suivant;
    }
    return NULL;
}

ElementPlat* chercherParNomPlat(ElementMenu* Em, char* nom) {
    ElementMenu* currentMenu = Em;
    while(currentMenu != NULL) {
        ElementPlat* currentPlat = currentMenu->menu.plats;
        while(currentPlat != NULL) {
            if(strcmp(currentPlat->plat.nom, nom) == 0) {
                return currentPlat;
            }
            currentPlat = currentPlat->suivant;
        }
        currentMenu = currentMenu->suivant;
    }
    return NULL;
}

ElementPlat* chercherParNomPlatDirect(ElementPlat* Ep, char* nom) {
    ElementPlat* current = Ep;
    while(current != NULL) {
        if(strcmp(current->plat.nom, nom) == 0) {
            return current;
        }
        current = current->suivant;
    }
    return NULL;
}

/* List Retrieval */
ElementPlat* getParCategorie(Menu M, char* categorie) {
    ElementPlat* result = NULL;
    ElementPlat* current = M.plats;
    while(current != NULL) {
        if(strcmp(current->plat.categorie, categorie) == 0) {
            ElementPlat* newElement = (ElementPlat*)malloc(sizeof(ElementPlat));
            newElement->plat = current->plat;
            newElement->suivant = result;
            result = newElement;
        }
        current = current->suivant;
    }
    return result;
}

ElementPlat* getPlatSupPrix(Menu M, float prix) {
    ElementPlat* result = NULL;
    ElementPlat* current = M.plats;
    while(current != NULL) {
        if(current->plat.prix > prix) {
            ElementPlat* newElement = malloc(sizeof(ElementPlat));
            newElement->plat = current->plat;
            newElement->suivant = result;
            result = newElement;
        }
        current = current->suivant;
    }
    return result;
}

ElementMenu* getMenuParNbrPlat(ElementMenu* Em) {
    ElementMenu* result = NULL;
    ElementMenu* current = Em;
    while(current != NULL) {
        int count = 0;
        ElementPlat* plat = current->menu.plats;
        while(plat != NULL) {
            count++;
            plat = plat->suivant;
        }
        if(count > 20) {
            ElementMenu* newElement = malloc(sizeof(ElementMenu));
            newElement->menu = current->menu;
            newElement->suivant = result;
            result = newElement;
        }
        current = current->suivant;
    }
    return result;
}

ElementMenu* getMenus(ElementMenu* Em) {
    ElementMenu* result = NULL;
    ElementMenu* current = Em;
    while(current != NULL) {
        int count = 0;
        float total = 0;
        ElementPlat* plat = current->menu.plats;
        while(plat != NULL) {
            count++;
            total += plat->plat.prix;
            plat = plat->suivant;
        }
        if(count > 20 && total <= 50) {
            ElementMenu* newElement = malloc(sizeof(ElementMenu));
            newElement->menu = current->menu;
            newElement->suivant = result;
            result = newElement;
        }
        current = current->suivant;
    }
    return result;
}

/* Ordered Insertion */
ElementPlat* ajoutParOrdrePrix(ElementPlat* Ep, Plat p) {
    ElementPlat* newElement = malloc(sizeof(ElementPlat));
    newElement->plat = p;
    newElement->suivant = NULL;
    newElement->precedent = NULL;

    if(Ep == NULL) {
        return newElement;
    }

    ElementPlat* current = Ep;
    ElementPlat* previous = NULL;

    while(current != NULL && current->plat.prix < p.prix) {
        previous = current;
        current = current->suivant;
    }

    if(previous == NULL) {
        newElement->suivant = Ep;
        Ep->precedent = newElement;
        return newElement;
    }

    previous->suivant = newElement;
    newElement->precedent = previous;
    newElement->suivant = current;
    if(current != NULL) {
        current->precedent = newElement;
    }

    return Ep;
}

ElementPlat* ajoutParOrdreNom(ElementPlat* Ep, Plat p) {
    ElementPlat* newElement = malloc(sizeof(ElementPlat));
    newElement->plat = p;
    newElement->suivant = NULL;
    newElement->precedent = NULL;

    if(Ep == NULL) {
        return newElement;
    }

    ElementPlat* current = Ep;
    ElementPlat* previous = NULL;

    while(current != NULL && strcmp(current->plat.nom, p.nom) < 0) {
        previous = current;
        current = current->suivant;
    }

    if(previous == NULL) {
        newElement->suivant = Ep;
        Ep->precedent = newElement;
        return newElement;
    }

    previous->suivant = newElement;
    newElement->precedent = previous;
    newElement->suivant = current;
    if(current != NULL) {
        current->precedent = newElement;
    }

    return Ep;
}

Menu ajouterParOrdreNomMenu(Menu M, Plat p) {
    M.plats = ajoutParOrdreNom(M.plats, p);
    return M;
}

/* Deletion Functions */
ElementPlat* supprimerParNom(ElementPlat* Ep, char* nom) {
    ElementPlat* current = Ep;
    while(current != NULL) {
        if(strcmp(current->plat.nom, nom) == 0) {
            if(current->precedent != NULL) {
                current->precedent->suivant = current->suivant;
            }
            if(current->suivant != NULL) {
                current->suivant->precedent = current->precedent;
            }
            ElementPlat* toReturn = (current == Ep) ? current->suivant : Ep;
            free(current);
            return toReturn;
        }
        current = current->suivant;
    }
    return Ep;
}

ElementPlat* supprimerParCategorie(ElementPlat* Ep, char* categorie) {
    ElementPlat* current = Ep;
    while(current != NULL) {
        if(strcmp(current->plat.categorie, categorie) == 0) {
            ElementPlat* next = current->suivant;
            if(current->precedent != NULL) {
                current->precedent->suivant = current->suivant;
            }
            if(current->suivant != NULL) {
                current->suivant->precedent = current->precedent;
            }
            ElementPlat* toDelete = current;
            current = current->suivant;
            free(toDelete);
            if(toDelete == Ep) {
                Ep = next;
            }
        } else {
            current = current->suivant;
        }
    }
    return Ep;
}

ElementMenu* supprimerParNbrPlat(ElementMenu* Em, int nbr) {
    ElementMenu* current = Em;
    while(current != NULL) {
        int count = 0;
        ElementPlat* plat = current->menu.plats;
        while(plat != NULL) {
            count++;
            plat = plat->suivant;
        }
        ElementMenu* next = current->suivant;
        if(count == nbr) {
            if(current->precedent != NULL) {
                current->precedent->suivant = current->suivant;
            }
            if(current->suivant != NULL) {
                current->suivant->precedent = current->precedent;
            }
            free(current);
            if(current == Em) {
                Em = next;
            }
        }
        current = next;
    }
    return Em;
}

/* Circular Linked List Versions */
ElementPlat* supprimerParNomCirculaire(ElementPlat* Ep, char* nom) {
    if(Ep == NULL) return NULL;
    
    ElementPlat* current = Ep;
    ElementPlat* start = Ep;
    ElementPlat* toReturn = Ep;
    
    do {
        if(strcmp(current->plat.nom, nom) == 0) {
            if(current->suivant == current) {
                free(current);
                return NULL;
            }
            current->precedent->suivant = current->suivant;
            current->suivant->precedent = current->precedent;
            if(current == toReturn) {
                toReturn = current->suivant;
            }
            ElementPlat* temp = current;
            current = current->suivant;
            free(temp);
        } else {
            current = current->suivant;
        }
    } while(current != start);
    
    return toReturn;
}

ElementPlat* supprimerParCategorieCirculaire(ElementPlat* Ep, char* categorie) {
    if(Ep == NULL) return NULL;
    
    ElementPlat* current = Ep;
    ElementPlat* start = Ep;
    ElementPlat* toReturn = Ep;
    int modified = 0;
    
    do {
        if(strcmp(current->plat.categorie, categorie) == 0) {
            modified = 1;
            if(current->suivant == current) {
                free(current);
                return NULL;
            }
            current->precedent->suivant = current->suivant;
            current->suivant->precedent = current->precedent;
            if(current == toReturn) {
                toReturn = current->suivant;
            }
            ElementPlat* temp = current;
            current = current->suivant;
            free(temp);
        } else {
            current = current->suivant;
        }
    } while(current != start || modified);
    
    return toReturn;
}

ElementMenu* supprimerParNbrPlatCirculaire(ElementMenu* Em, int nbr) {
    if(Em == NULL) return NULL;
    
    ElementMenu* current = Em;
    ElementMenu* start = Em;
    ElementMenu* toReturn = Em;
    int modified = 0;
    
    do {
        int count = 0;
        ElementPlat* plat = current->menu.plats;
        if(plat != NULL) {
            ElementPlat* pStart = plat;
            do {
                count++;
                plat = plat->suivant;
            } while(plat != pStart);
        }
        
        ElementMenu* next = current->suivant;
        if(count == nbr) {
            modified = 1;
            if(current->suivant == current) {
                free(current);
                return NULL;
            }
            current->precedent->suivant = current->suivant;
            current->suivant->precedent = current->precedent;
            if(current == toReturn) {
                toReturn = current->suivant;
            }
            free(current);
        }
        current = next;
    } while(current != start || modified);
    
    return toReturn;
}

/* Main function for testing */
int main() {
    // You can add test code here
    return 0;
}