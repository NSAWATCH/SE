#include <stdio.h>
#include <stdlib.h>
// gestion des chaines:
#include <string.h>
// open, read, write:
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAILLE_MAX_NOM_BASE 50

#define MAGIC_H "hash"
#define MAGIC_BLK "blkr"
#define MAGIC_DKV "drpt"
#define MAGIC_KV "stcv"

int hachageProf(char *valeur);
int creerBase( char *nom );
int creerFichier( char *nom, char *extension, char* magicNumber);
// revoie -1 si existe, 0 sinon:
int baseExiste(char *nom); 

int main(int argc, char **argv){
	
	/*
	char *test = "yo:k:mjbsdqkhsqefljzejklo";	
	int hachTest = hachageProf(test);
	printf("%s: %d\n", test, hachTest );
	*/
	
	char *nomBaseTest = "yolo";
	
	creerBase( nomBaseTest );
	
	printf("SWAG\n");	
	
	return 0;
}

int baseExiste(char *nom){

	printf("Test branch salut !\n");

	int res = 0;
	char nomDefinitif[512];
	strcpy(nomDefinitif, nom);
	
	snprintf(nomDefinitif, 512, "%s.h", nom);
	res += access(nomDefinitif, F_OK);
	
	snprintf(nomDefinitif, 512, "%s.blk", nom);
	res += access(nomDefinitif, F_OK);
	
	snprintf(nomDefinitif, 512, "%s.kv", nom);
	res += access(nomDefinitif, F_OK);
	
	snprintf(nomDefinitif, 512, "%s.dkv", nom);
	res += access(nomDefinitif, F_OK);

	if( res != -4 )
		return -1;
	else	
		return 0;

}

int creerFichier( char *nom, char *extension, char* magicNumber){

	//PDTC

	int fd;
	char nomDefinitif[512];
	strcpy(nomDefinitif, nom);

	snprintf(nomDefinitif, 512, "%s.%s", nom, extension);
	if( (fd = open( nomDefinitif, O_CREAT | O_WRONLY, 0777 ) ) == -1 ){
		fprintf(stderr, "Erreur à la création de %s\n", nomDefinitif );
		exit(1);
	}	
	if( write(fd, magicNumber, 4) != 4){
		fprintf(stderr, "Erreur à la création de %s\n", nomDefinitif );
		exit(1);
	}	
	printf("%s créé avec succès avec le magic number %s\n", nomDefinitif, magicNumber);
	close( fd );
		
}

int creerBase( char *nom ){
	
	char nomDefinitif[512];
	
	if( strlen( nom ) > TAILLE_MAX_NOM_BASE ){
		fprintf(stderr, "Un nom de base ne peut dépasser %d caractères\n", TAILLE_MAX_NOM_BASE);
		exit(1);
	}
	
	if( baseExiste( nom ) != 0 ){ //TO DO
		fprintf(stderr, "Un ou plusieurs fichiers de base avec le nom %s existe déjà\n", nom);
		exit( 1 );
	}
	
	// création de nom.h:	
	creerFichier(nom, "h", MAGIC_H);
	
	// création de nom.blk:	
	creerFichier(nom, "blk", MAGIC_BLK);
	
	// création de nom.kv:	
	creerFichier(nom, "kv", MAGIC_KV);
	
	// création de nom.dkv:	
	creerFichier(nom, "dkv", MAGIC_DKV);
	
	return 0;
}

int hachageProf(char *valeur){
	
	int hachCode = 0;
	int i = 0;
	
	while( valeur[i] != '\0' ){
		hachCode += valeur[i];
		i++;		
	}
	
	hachCode %= 999983;
	
	return hachCode;
}

