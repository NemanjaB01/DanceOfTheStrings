// <a2>.c
//
// < This program takes users input as string and makes sentences >
// <after that user is asked which option he wants to choose to manipulate with these sentences>
//
// Group: <group Simone F>
//
// Author: <12037057>
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>

#define START_LEGNTH 50

// takes two parameters text and text index 
// counts until it comes to null charachter and returns that value

int sentenceLength(char *text, int text_index)
{
  int i = 0;
  for (; text[text_index] != '\0'; text_index++)
  {
      i++;
  }
  return i;
}


// takes two parameters sentences and number of sentences
// counts lower and upper cases, total number of cases ,signs and sentences
// return no value

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


//takes no parameter 
// clean stdin and reurn value one

int clean()
{
  while (getchar()!= '\n');
  return 1;
}


//takes two parameters sentences and number of sentences
//ask user to enter numbers of sentences he wants to replace
//return changed sentences

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
    int first_sentence = 0;
    int second_sentence = 0;
    char input_check;
    do
    {
      printf("Nummer des ersten Satzes: ");

    } while ((( scanf("%d%c", &first_sentence,&input_check) != 2 || input_check != '\n') && clean()) 
    ||  first_sentence > *num_sentences || first_sentence <= 0);

    do
    {
      printf("Nummer des zweiten Satzes: ");

    } while ((( scanf("%d%c", &second_sentence,&input_check) != 2 || input_check != '\n') && clean()) || 
    second_sentence > *num_sentences || second_sentence <= 0 || second_sentence == first_sentence);

    printf("\n");
    char *sentence_1 = sentences[first_sentence - 1];
    char *sentence_2 = sentences[second_sentence - 1];
    sentences[first_sentence - 1] = sentence_2;
    sentences[second_sentence - 1] = sentence_1;

    return sentences;
  }
}


// takes two parametes sentences and number of sentences
// prints sentences without number in one line
// return no value

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


// takes two parameters sentences and number of sentences 
// asks user to enter numbers of sentences he wants to connect
// sentences will be connected with 'und' and last character from frist sentence will be deleted
// return changed sentences

char **connectSentence(char **sentences, int *num_sentences)
{
  int first_sentence = 0;
  int second_sentence = 0;
  char input_check;

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
    } while ((( scanf("%d%c", &first_sentence,&input_check) != 2 || input_check != '\n') && clean()) 
    ||first_sentence > *num_sentences || first_sentence <= 0);

    do
    {
      printf("Nummer des zweiten Satzes: ");

    } while ((( scanf("%d%c", &second_sentence,&input_check) != 2 || input_check != '\n') && clean()) 
    ||second_sentence > *num_sentences || second_sentence <= 0 || second_sentence == first_sentence);
  }

  printf("\n");
  char *sentence_1 = sentences[first_sentence - 1];
  char *sentence_2 = sentences[second_sentence - 1];

  int s1_length = sentenceLength(sentence_1, 0);

  int total_size = s1_length + 5 + sentenceLength(sentence_2, 0) ;
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


// takes two parameters sentences and number of sentences
// prints sentences with numbers in separeted lines
// return no value

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


// takes no parameter
// prints choice menu and return no value

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


// takes two parameters text and number
// goes through text when he encounters a particular sign
// return new made sentences

char **makeSentences(char *text, int *num)
{
  int end_of_sentences = 0;
  for(int index = 0;text[index] != '\0';index ++)
  {
    char tmp = text[index];
    if(tmp == '.' || tmp == '!' || tmp == '?')
    {
      end_of_sentences ++;
    }
  }
  int num_sentences = 0;
  int max_num_sentence = end_of_sentences;
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
    free(sentences);
    return NULL;
  }

  for (int text_index = 0; text[text_index] != '\0' && text + text_index != NULL; text_index++)
  {
    char tmp = text[text_index];
    if ((tmp == ' ' || tmp == '\t') && sentence_length == 0)
    {
      continue;
    }

    if (max_sentence_length - 1 == sentence_length)
    {
      max_sentence_length += 20;
      current_sentence = (char *)realloc(current_sentence, max_sentence_length * sizeof(char));
       if(current_sentence == NULL)
       {
         free(sentences);
          return NULL;
       }
    }
    current_sentence[sentence_length++] = tmp;

    if (tmp == '.' || tmp == '?' || tmp == '!') 
    {
      current_sentence[sentence_length++] = '\0';
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


// takes no parameter
// takes user input from stdin
// return user input type string
char *userInput()
{
  size_t current_len = 0;
  size_t text_len = 0;

  char *text = (char*)calloc(START_LEGNTH, sizeof(char));
  if(text == NULL)
  {
    return NULL;
  }
  do
  {
    fgets(text + text_len , START_LEGNTH , stdin);
    current_len = sentenceLength(text, text_len);
    if(current_len == (START_LEGNTH - 1 ))
    {
      text_len += current_len;
      char *tmp =(char*)realloc(text,(text_len + START_LEGNTH)  * sizeof(char));
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
  } while ((START_LEGNTH - 1  == current_len) && (text[text_len- 1] != '\n'));

  text[text_len++] = '\0';

  return text;
}


// takes two parameters sentences and numbeer of sentences
// asks user for his choice of function until option 'e' is choosen
// return no value

void userChoice(char **sentences,int num_sentences)
{
  int input, user_choice;
  int check_input = 1;
  selectMenu();
  while (check_input > 0)
  {
    int num_charachters = 0;
    printf("Ihre Wahl: ");
    check_input = 0;
    while (EOF != (input = getchar()) && input != '\n')
    {
      num_charachters ++;
      if (((input != 't')&& (input != 'p') && (input != 'o')&& (input != 's')
       && (input != 'c') && (input != 'e')))
      {
        check_input++;
      }
      user_choice = input;
    }
    if (check_input == 0 && num_charachters == 1)
    {
      check_input = 1;
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
   check_input ++;
  }
  for (int i = 0; i < num_sentences; i++)
  {
    free(sentences[i]);
  }
  free(sentences);
}


// tha main program
// takes no parameter 
// calls functions and checks for possible errors
// return always 0

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
  else if(num_sentences > 0)
  {
    int text_index = 0 ;
    while(text[text_index] != '\0')
    {
      text_index++;
    }
    char tmp = text[text_index - 2];
    if (tmp != '!' && tmp != '?' && tmp != '.') 
    {
      free(text);
      for (int i = 0; i < num_sentences; i++)
      {
        free(sentences[i]);
      }
      free(sentences);
      printf("Der Text endet ohne Satzzeichen!\n");
      return 2;
    }
  }
  printf("\n");
  userChoice(sentences,num_sentences);
  free(text);
  return 0;
}

