/* dict.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
#if 0
	char *desc = "stardict", *word = "hello", 
	     *trans = "哈喽啊，饭已ok啦，下来米西米西吧！";
	FILE *fp;
	int i, j, cnt, word_cnt = 1, trans_cnt = 1;

	/* write to file */
	fp = fopen("dict.dat", "w");
	/* description */
	cnt = strlen(desc) + 1;
	fwrite(desc, 1, cnt, fp);
	/* all word count */
	fwrite(&word_cnt, 1, 4, fp);
	for (i = 0; i < word_cnt; ++i) {
		/* per word length */
		cnt = strlen(word) + 1;
		fwrite(&cnt, 1, 4, fp);
		/* per word content */
		fwrite(word, 1, cnt, fp);	

		/* translations count corresponding to a word */
		fwrite(&trans_cnt, 1, 4, fp);
		for (j = 0; j < trans_cnt; ++j) {
			/* per translation length */
			cnt = strlen(trans) + 1;
			printf("%d\n", cnt);
			fwrite(&cnt, 1, 4, fp);
			/* per translation content */
			fwrite(trans, 1, cnt, fp);
		}
	}
	fclose(fp);
	return 0;
#endif

	FILE *fp;
	char desc[9], *word, *trans;
	int i, j, word_cnt, trans_cnt, cnt;

	/* the length of string read from file contains '\0' */
	/* read from file */
	fp = fopen("dict.dat", "r");
	/* description */
	fread(desc, 1, 9, fp);
	printf("%s", desc);
	/* all word count */
	fread(&word_cnt, 1, 4, fp);
	//printf("%d", word_cnt);

	for (i = 0; i < word_cnt; ++i) {
		/* per word length */
		fread(&cnt, 1, 4, fp);
		//printf("%d", cnt);
		/* per word content */
		word = malloc(cnt);
		fread(word, 1, cnt, fp);
		printf("%s", word);

		/* translations count corresponding to a word */
		fread(&trans_cnt, 1, 4, fp);
		//printf("%d", trans_cnt);
		
		for (j = 0; j < trans_cnt; ++j) {
			/* per translation length */
			fread(&cnt, 1, 4, fp);
			//printf("%d", cnt);
			/* per translation content */
			trans = malloc(cnt);
			fread(trans, 1, cnt, fp);
			//printf("%s", trans);
		}
	}	
	free(word);
	free(trans);
	fclose(fp);
	return 0;
}
