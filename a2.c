// <a2>.c
//
// < This program takes users inputs to calculate necessary fire-fighting pumps
// > <In this process program calucate different formulas to get coordinates for
// pumps>
//
// Group: <group Simone F>
//
// Author: <12037057>
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>

#define STARTLEGNTH 20


int sentenceLength(char *text, int text_index)
{
  int i = 0;
  for (; text[text_index] != '\0'; text_index++)
  {
      i++;
  }
  return i;
}


void textStatistic(char **sentences, int *num_sentences)
{
  int is_lower = 0;
  int is_upper = 0;
  int text_index = 0;
  int signs = 0;
  int i = 0;
  while(i < *num_sentences)
  {
    char *tmp2 = sentences[i];
    char tmp = tmp2[text_index];
    for (; tmp != '\0'; text_index++)
    {
      tmp2 = sentences[i];
      tmp = tmp2[text_index];
      if (tmp != ' ' && tmp != '\0')
      {
        signs++;
        if (tmp > 64 && tmp < 91)
        {
          is_upper++;
        }
        else if (tmp > 96 && tmp < 123)
        {
          is_lower++;
        }
      }
    }
    i++;
    text_index = 0;
  }
  printf("Text Statistik:\n");
  printf("%d Sätze, %d Zeichen\n", *num_sentences, signs);
  printf("%d Buchstaben (%d Großbuchstaben, %d Kleinbuchstaben)\n", is_upper + is_lower, is_upper, is_lower);
  printf("\n");
}


char **replaceSentences(char **sentences, int *num_sentences)
{
  if (*num_sentences == 1)
  {
    printf("Nur noch ein Satz vorhanden!\n");
    printf("\n");
    return sentences;
  }
  else
  {
    int firstSentence = 0;
    int secondSentence = 0;
    do
    {
      printf("Nummer des ersten Satzes: ");
      scanf("%d", &firstSentence);
      getchar();
    } while (firstSentence > *num_sentences || firstSentence < 0);

    do
    {
      printf("Nummer des zweiten Satzes: ");
      scanf("%d", &secondSentence);
      getchar();
    } while (secondSentence > *num_sentences || secondSentence < 0 || secondSentence == firstSentence);

    printf("\n");
    char *sentence_1 = sentences[firstSentence - 1];
    char *sentence_2 = sentences[secondSentence - 1];
    sentences[firstSentence - 1] = sentence_2;
    sentences[secondSentence - 1] = sentence_1;

    return sentences;
  }
}

void printSenteceWithoutNum(char **sentences, int *num_sentences)
{
  printf("Text:\n");
  int i = 0;
  int text_index = 0;
  for (; i < *num_sentences; i++)
  {

    printf("%s ", sentences[i]);
    text_index = 0;
  }
  printf("\n\n");
}

char **connectSentence(char **sentences, int *num_sentences)
{
  int first_sentence = 0;
  int second_sentence = 0;

  if (*num_sentences == 1)
  {
    printf("Nur noch ein Satz vorhanden!\n");
    printf("\n");
    return sentences;
  }
  else
  {
    do
    {
      printf("Nummer des ersten Satzes: ");
      scanf("%d", &first_sentence);
      getchar();
    } while (first_sentence > *num_sentences || first_sentence < 0);

    do
    {
      printf("Nummer des zweiten Satzes: ");
      scanf("%d", &second_sentence);
      getchar();
    } while (second_sentence > *num_sentences || second_sentence < 0 || second_sentence == first_sentence);
  }

  printf("\n");
  char *sentence_1 = sentences[first_sentence - 1];
  char *sentence_2 = sentences[second_sentence - 1];

  int s1_length = sentenceLength(sentence_1, 0);

  int total_size = s1_length - 1 + 4 + sentenceLength(sentence_2, 0) + 1;
  sentence_1 = (char *)realloc(sentence_1, sizeof(char) * total_size);
  if(sentence_1 == NULL)
  {
    printf("Zu wenig Speicher vorhanden!\n");
    return sentences;
  }

  int i = s1_length - 1;

  sentence_1[i++] = ' ';
  sentence_1[i++] = 'u';
  sentence_1[i++] = 'n';
  sentence_1[i++] = 'd';
  sentence_1[i++] = ' ';

  for (int j = 0; sentence_2[j] != '\0'; ++j)
  {
    sentence_1[i++] = sentence_2[j];
  }

  sentence_1[i] = '\0';
  sentences[first_sentence - 1] = sentence_1;

  int start = second_sentence - 1;
  int end = *num_sentences - 1;

  while (start < end)
  {
    sentences[start] = sentences[start + 1];
    start++;
  }

  int new_size = *num_sentences - 1;
  *num_sentences = new_size;
  free(sentence_2);
  sentences = (char **)realloc(sentences, new_size * sizeof(char *));
  if(sentences == NULL)
  {
    printf("Zu wenig Speicher vorhanden!\n");
    return sentences;
  }
  return sentences;
}

void printSentencesWithNum(char **sentences, int *num_sentences)
{
  printf(" Nr. | Satz\n");
  printf("-----+----------------------------------------\n");
  int i;

  for (i = 0; i < *num_sentences; i++)
  {

    printf("%4d | %s\n", i + 1, sentences[i]);
  }
  printf("\n");
}


void selectMenu()
{
  printf("Wählen Sie eine Option:\n");
  printf("  t: Text-Statistik\n");
  printf("  s: Zwei Sätze vertauschen\n");
  printf("  c: Zwei Sätze zusammenketten\n");
  printf("  p: Text mit Zeilennummer ausgeben\n");
  printf("  o: Text ohne Zeilennummer ausgeben\n");
  printf("  e: Programm beenden\n");
  printf("\n");
}

char **makeSentences(char *text, int *num)
{

  int num_sentences = 0;
  int max_num_sentence = 5;
  int initial_sentence_length = 20;
  int max_sentence_length = 20;
  int sentence_length = 0;
  char **sentences = (char **)calloc(max_num_sentence, sizeof(char *));
  if(sentences == NULL)
  {
    return NULL;
  }
  char *current_sentence = (char *)calloc(initial_sentence_length, sizeof(char));
   if(current_sentence == NULL)
  {
    return NULL;
  }

  for (int text_index = 0; text[text_index] != '\0' && text + text_index != NULL; text_index++)
  {
    char tmp = text[text_index];
    if (tmp == ' ' && sentence_length == 0 && num_sentences > 0)
    {
      continue;
    }

    if (max_sentence_length - 1 == sentence_length)
    {
      max_sentence_length += 20;
      current_sentence = (char *)realloc(current_sentence, max_sentence_length * sizeof(char));
       if(current_sentence == NULL)
       {
          return NULL;
       }
    }
    current_sentence[sentence_length++] = tmp;

    if (tmp == '.' || tmp == '?' || tmp == '!') 
    {
      if (num_sentences == max_num_sentence) 
      {
        max_num_sentence += 2;
        sentences = (char **)realloc(sentences, max_num_sentence * sizeof(char));
         if(sentences == NULL)
         {
            return NULL;
         }
      }
      current_sentence[sentence_length] = '\0';
      sentences[num_sentences++] = current_sentence;
      max_sentence_length = 20;
      sentence_length = 0;
      current_sentence = (char *)calloc(initial_sentence_length, sizeof(char));
      if(current_sentence == NULL)
      { 
        free(sentences);
        return NULL;
      }

    }
  }
  *num = num_sentences;
  free(current_sentence);
  return sentences;
}


char *userInput()
{
  size_t current_len = 0;
  size_t text_len = 0;

  char *text = (char*)calloc(STARTLEGNTH, sizeof(char));
  if(text == NULL)
  {
    return NULL;
  }
  do
  {
    fgets(text + text_len , STARTLEGNTH , stdin);
    current_len = sentenceLength(text, text_len);
    if(current_len == (STARTLEGNTH - 1 ))
    {
      text_len += current_len;
      char *tmp =(char*)realloc(text,(text_len + STARTLEGNTH)  * sizeof(char));
      if(tmp == NULL)
      {
        free(text);
        return NULL;
      }
      else
      {
        text = tmp;
      }
    }
    else
    {
      text_len += current_len;
    }
  } while ((STARTLEGNTH - 1  == current_len) && (text[text_len- 2] != '\n'));

  text[text_len++] = '\0';

  return text;
}


int main()
{
  printf("Bitte Text eingeben:");
  char **sentences = NULL;
  char *text = userInput();
  if (text == NULL) 
  {
    printf("Zu wenig Speicher vorhanden!\n");
    return 3;
  }
  printf("\n");
  int num_sentences = 0;
  sentences = makeSentences(text, &num_sentences);
  if(sentences == NULL)
  {
    free(text);
    printf("Zu wenig Speicher vorhanden!\n");
    return 3;
  }

  if (num_sentences == 0)
  {
    printf("Kein Satz gefunden!\n");
    free(text);
    for (int i = 0; i < num_sentences; i++) 
    {
      free(sentences[i]);
    }
    free(sentences);
    return 1;
  }
  /*else if(num_sentences > 0)
  {
    int text_index = 0 ;
    while(text[text_index] != '\0')
    {
      text_index++;
    }
    if (text[text_index ] != '!' && text[text_index] != '?' && text[text_index] != '.') 
    {
      printf("Der Text endet ohne Satzzeichen!\n");
      return 2;
    }
  }*/
  printf("\n");
  int input, user_choice;
  int space = 1;
  selectMenu();
  while (space > 0) 
  {
    printf("Ihre Wahl: ");
    space = 0;
    while (EOF != (input = getchar()) && input != '\n') 
    {
      if (input == ' ') 
      {
        space++;
      }
      user_choice = input;
    }
    if (space == 0) 
    {
      space = 1;
      if (user_choice == 't' || user_choice == 'p' || user_choice == 'o' || user_choice == 's' || user_choice == 'c' || user_choice == 'e')
      {
        if (user_choice == 't')
        {
          textStatistic(sentences, &num_sentences);
        }
        else if (user_choice == 'p')
        {
          printSentencesWithNum(sentences, &num_sentences);
        }
        else if (user_choice == 'o') 
        {
          printSenteceWithoutNum(sentences, &num_sentences);
        } 
        else if (user_choice == 's') 
        {
          sentences = replaceSentences(sentences, &num_sentences);
        } 
        else if (user_choice == 'c') 
        {
          sentences = connectSentence(sentences, &num_sentences);
        } 
        else if (user_choice == 'e') 
        {
          printf("Programmende!\n");
          break;
        }
        selectMenu();
      }
    }
  }
  free(text);
  for (int i = 0; i < num_sentences; i++)
  {
    free(sentences[i]);
  }
  free(sentences);
  return 0;
}