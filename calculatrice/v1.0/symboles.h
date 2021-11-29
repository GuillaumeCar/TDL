/**
* \struct symbol_t
* \brief Définition du type de données "symbole"
*/
typedef struct symbol
{
    char *name; // Nom du symbole : identifiant
    short type; // Type du symbole : IVAR, FVAR, UNDEF
    union
    {                // Selon le type du symbole :
        int iVal;    // une valeur entière si le type est IVAR
        double dVal; // une valeur réelle si le type est FVAR
    } U;
    struct symbol *next; // Pointeur sur symbole suivant
} symbol_t;

/**
* \typedef  pSymbol_t
* \brief    Définition du type de données "pointeur sur symbole"
*/
typedef struct symbol *pSymbol_t;

/**
* \def      SYMBOL_NULL
* \brief    Définition du symbole nul
*/
#define SYMBOL_NULL ((pSymbol_t)0)

/**
* \fn symbol_t* installSymbol (char* tokenName, short tokenType)
* \brief Insérer un nouveau symbole en tête de la liste des symboles
* \return pointeur sur symbole inséré
*/
symbol_t *installSymbol(char *tokenName, short tokenType);
/**
* \fn symbol_t* lookUpSymbol (const char *tokenName)
* \brief Rechercher un symbole dans la liste des symboles
* \return pointeur sur symbole recherché ou NULL si non trouvé
*/
symbol_t *lookUpSymbol(const char *tokenName);
