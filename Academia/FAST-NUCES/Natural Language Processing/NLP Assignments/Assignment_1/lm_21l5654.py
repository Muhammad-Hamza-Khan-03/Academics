import os.path
import sys
import random
from operator import itemgetter
from collections import defaultdict

import math # for taking log in perplexity

def readFileToCorpus(f):

    if os.path.isfile(f):
        file = open(f, "r") # open the input file in read-only mode
        i = 0 # this is just a counter to keep track of the sentence numbers
        corpus = [] # this will become a list of sentences
        print("Reading file ", f)
        for line in file:
            i += 1
            sentence = line.split() # split the line into a list of words
            #append this lis as an element to the list of sentences
            corpus.append(sentence)
        #    if i % 1000 == 0:
    	#print a status message: str(i) turns int i into a string
    	#so we can concatenate it
        #        sys.stderr.write("Reading sentence " + str(i) + "\n")
        #endif
    #endfor
        return corpus
    else:
    #ideally we would throw an exception here, but this will suffice
        print("Error: corpus file ", f, " does not exist")
        sys.exit() # exit the script
    #endif
#enddef

# Preprocess the corpus
def preprocess(corpus):
    #find all the rare words
    freqDict = defaultdict(int)
    for sen in corpus:
	    for word in sen:
	       freqDict[word] += 1
	    #endfor
    #endfor

    #replace rare words with unk
    for sen in corpus:
        for i in range(0, len(sen)):
            word = sen[i]
            if freqDict[word] < 2: # rare words freq <2 
                sen[i] = UNK
	        #endif
	    #endfor
    #endfor

    #bookend the sentences with start and end tokens
    for sen in corpus:
        sen.insert(0, start)
        sen.append(end)
    #endfor
    
    return corpus
#enddef

# corpus bookmarks and add # UNK
def preprocessTest(vocab, corpus):
    #replace test words that were unseen in the training with unk
    for sen in corpus:
        for i in range(0, len(sen)):
            word = sen[i]
            if word not in vocab: # Unseen words
                sen[i] = UNK
	    #endif
	#endfor
    #endfor
    
    #bookend the sentences with start and end tokens
    for sen in corpus:
        sen.insert(0, start)
        sen.append(end)
    #endfor

    return corpus
#enddef

# Constants 
UNK = "UNK"     # Unknown word token
start = "<s>"   # Start-of-sentence token
end = "</s>"    # End-of-sentence-token


#--------------------------------------------------------------
# Language models and data structures
#--------------------------------------------------------------

# Parent class for the three language models you need to implement
class LanguageModel:
    # Initialize and train the model (ie, estimate the model's underlying probability
    # distribution from the training corpus)
    def __init__(self, corpus):
        print("""Your task is to implement four kinds of n-gram language models:
      a) an (unsmoothed) unigram model (UnigramModel)
      b) a unigram model smoothed using Laplace smoothing (SmoothedUnigramModel)
      c) an unsmoothed bigram model (BigramModel)
      d) a bigram model smoothed using linear interpolation smoothing (SmoothedBigramModelInt)
      """)
    #enddef

    # Generate a sentence by drawing words according to the 
    # model's probability distribution
    # Note: think about how to set the length of the sentence 
    #in a principled way
    def generateSentence(self):
        sentence = []
        sentence.append(start) # sentence starts with <s> marker
        
        current = start

        while(current != end): #till </s> marker
            
            word = random.choice(list(self.word_counts))
            current = word
            sentence.append(current)

        return sentence
    #emddef

    # Given a sentence (sen), return the probability of 
    # that sentence under the model
    def getSentenceProbability(self, sentence):
        pass
    #enddef

    # Given a corpus, calculate and return its perplexity 
    #(normalized inverse log probability)
    def getCorpusPerplexity(self, corpus):
        size_of_sen = 0
        curr_perplexity = 0
        for sen in corpus:
            size_of_sen+=len(sen)
            curr_perplexity+=math.log(self.getSentenceProbability(sen),2) # taking Log because of very small perplexity value log(p) = log(p1)+log(p2)+...
        
        perplexity = 2**((-1/size_of_sen)*curr_perplexity) # formula
        return perplexity 
    #enddef

    # Given a file (filename) and the number of sentences, generate a list
    # of sentences and write each to file along with its model probability.
    # Note: you shouldn't need to change this method
    def generateSentencesToFile(self, numberOfSentences, filename):
        
        print("Writing in :",filename)

        filePointer = open(filename, 'w+')
        for i in range(0,numberOfSentences):
            sen = self.generateSentence()
            prob = self.getSentenceProbability(sen)

            # stringGenerated = str(prob) + " " + " ".join(sen) 
            # print(stringGenerated, end="\n", file=filePointer)
        print("Wriiten")    
	#endfor
    #enddef
#endclass

#---------------------------- 
# Unigram model starts here 
# ---------------------------

# Unigram language model
class UnigramModel(LanguageModel):
    def __init__(self, corpus,testing_corpus):
        self.word_total = 0.0
        self.word_counts = defaultdict(float)
        self.test_corpus = testing_corpus
        self.train_model(corpus)
    
    #train Unigram Model
    def train_model(self,corpus): # get count of total words and vocab words
        for sentence in corpus:
            for word in sentence:
                if word != start:
                    self.word_counts[word] += 1.0
                    self.word_total +=1.0

    #Calculating probability of a word
    def calculate_probability(self,word):
        c = self.word_counts[word]
        n = self.word_total

        return c/n # getting probability for each word in corpus
    
    def generateSentence(self):
        
        sentence = []
        sentence.append(start) # sentence starts with <s> marker
        
        current = start

        while(current != end): #till </s> marker
            
            word = random.choice(list(self.word_counts))
            current = word
            sentence.append(current)

        return sentence

    def getSentenceProbability(self,sentence):

        current_prob = 1

        for index,word in enumerate(sentence):
            if word != start:
                current_prob *= self.calculate_probability(word) 
        
        return current_prob #prob of each word except start marker

    def getCorpusPerplexity(self,corpus):
        size_of_sen = 0
        curr_perplexity = 0
        for sen in corpus:
            size_of_sen+=len(sen)
            curr_perplexity+=math.log(self.getSentenceProbability(sen),2) # taking Log because of very small perplexity value log(p) = log(p1)+log(p2)+...
        
        perplexity = 2**((-1/size_of_sen)*curr_perplexity) # formula
        return perplexity
    
    def generateSentencesToFile(self, numberOfSentences, filename):
        print("writing file," , filename)
        filePointer = open(filename, 'w+')
        
        for i in range(0,numberOfSentences):
            
            sen = self.generateSentence()
            prob = self.getSentenceProbability(sen)

            stringGenerated = str(prob) + " " + " ".join(sen) 
            print(stringGenerated, end="\n", file=filePointer)
#endclass

#Smoothed unigram language model (use laplace for smoothing)
class SmoothedUnigramModel(LanguageModel):
    def __init__(self, corpus,vocab,testing_corpus):
        self.word_total = 0.0
        self.word_counts = defaultdict(float)
        self.test_corpus = testing_corpus
        self.train_model(corpus)
        self.vocab_size = len(vocab)
    #endddef

    def train_model(self,corpus):
        
        for sentence in corpus:
            for word in sentence:
                if word !=start:
                    self.word_counts[word]+=1.0
                    self.word_total = self.word_total+1.0
        
    def calculate_probability(self,word):
        c = self.word_counts[word]
        n = self.word_total
        v = self.vocab_size
        return (c+1)/(n+v) #prob based on smoothing

    def generateSentence(self):
        sentence = []
        sentence.append(start) # sentence starts with <s> marker
        
        current = start

        while(current != end): #till </s> marker
            
            word = random.choice(list(self.word_counts))
            current = word
            sentence.append(current)

        return sentence
        


    def getSentenceProbability(self,sentence):
        
        current_prob = 1

        for index,word in enumerate(sentence):
            if word != start:
                current_prob *= self.calculate_probability(word)
        
        return current_prob

    def getCorpusPerplexity(self,corpus):
        size_of_sen = 0
        curr_perplexity = 0
        for sen in corpus:
            size_of_sen+=len(sen)
            curr_perplexity+=math.log(self.getSentenceProbability(sen),2) # taking Log because of very small perplexity value log(p) = log(p1)+log(p2)+...
        
        perplexity = 2**((-1/size_of_sen)*curr_perplexity) # formula
        return perplexity        
    def generateSentencesToFile(self,numberOfSentences,filename):
        print("writing file," , filename)
        filePointer = open(filename, 'w+')
        
        for i in range(0,numberOfSentences):
            
            sen = self.generateSentence()
            prob = self.getSentenceProbability(sen)

            stringGenerated = str(prob) + " " + " ".join(sen) 
            print(stringGenerated, end="\n", file=filePointer)
        
#endclass

#---------------------------- 
# Bigram model starts here 
# ---------------------------

# Unsmoothed bigram language model
class BigramModel(LanguageModel):
    def __init__(self, corpus, vocab, test_corpus):
        self.word_counts = {}
        self.pair_counts = {}
        self.total_words = 0
        self.next_words = {}
        self.vocab_size = len(vocab)
        self.test_corpus = test_corpus
        self.train(corpus)

    def train(self, corpus):
        for sentence in corpus:
            for idx, word in enumerate(sentence):
                self.word_counts[word] = self.word_counts.get(word, 0) + 1
                self.total_words += 1
                if idx > 0:
                    prev_word = sentence[idx - 1]
                    self.pair_counts[(prev_word, word)] = self.pair_counts.get((prev_word, word), 0) + 1
                    if prev_word in self.next_words:
                        self.next_words[prev_word].add(word)
                    else:
                        self.next_words[prev_word] = {word}

    def probability(self, word_pair): #if prev word in word_counts list then get prob else 0
        prev_word, word = word_pair
        if prev_word in self.word_counts:
            return self.pair_counts.get(word_pair, 0) / self.word_counts[prev_word]
        return 0

    def getSentenceProbability(self, sentence):
        
        if(len(sentence) == 1):
            return 0

        probability = 0
        # is_first = True
        # for idx, word in enumerate(sentence):
        #     if idx != 0:
        #         if is_first:
        #             probability = self.probability((sentence[idx - 1], word))
        #             is_first = False
        #         else:
        #             probability *= self.probability((sentence[idx - 1], word))
        probability = self.probability((sentence[0], sentence[1]))
        for idx in range(2, len(sentence)):
            word_pair = (sentence[idx - 1], sentence[idx])
            
            word_pair_probability = self.probability(word_pair)
            
            if word_pair_probability == 0:
                return 0
            
            probability *= word_pair_probability

        return probability
        
    def generate_sentence(self, start):
        init_word = start
        final_sentence = [init_word]
        while init_word != end:
            next_options = self.next_words.get(init_word, [])
            selected_option = random.choice(list(next_options))
            init_word = selected_option
            final_sentence.append(init_word)
        return final_sentence

    def getCorpusPerplexity(self, test_corpus):
        total_words =0
        perplex = 0
        for sentence in test_corpus:
            total_words+=len(sentence)
            probability = self.getSentenceProbability(sentence)
            if probability > 0:
                perplex += math.log(probability,2)
        perplexity = 2 ** ((-1 / total_words) * perplex)
        return perplexity
    
    
    def generate_sentence_bg(self):
        sen = self.generateSentence()
        prob = self.getSentenceProbability(sen)

        sentence_generated = str(prob) + " " + " ".join(sen) 
        print("bigram Unsmoothed:\n",sentence_generated)
    
    def generateSentencesToFile(self,numberOfSentences,filename):
        print("Writing Unsmoothed Bigram in file",filename)
        filePointer = open(filename, 'w+')
        
        for i in range(0,numberOfSentences):

            sen = self.generateSentence()
            prob = self.getSentenceProbability(sen)

            stringGenerated = str(prob) + " " + " ".join(sen) 
            print(stringGenerated, end="\n", file=filePointer)
        

# Smoothed bigram language model (use linear interpolation for smoothing, set lambda1 = lambda2 = 0.5)
class LinearInterpolationModel(LanguageModel):


    def __init__(self, corpus, vocab, test_corpus):
        self.counts = defaultdict(float)
        self.pairCounts = defaultdict(float)
        self.total = 0.0
        self.vocab_size = len(vocab)
        self.train(corpus)
        self.test_corpus = test_corpus
        self.lambda1 = 0.5
        self.lambda2 = 0.5

    def train(self, corpus):
        for sen in corpus:
            for idx, word in enumerate(sen):
                self.counts[word] += 1.0
                self.total += 1.0
                if idx > 0:
                    self.pairCounts[(sen[idx-1], word)] += 1 # get count of unique pair words

    def prob(self, word_pair):
        word0, word1 = word_pair
        p1 = self.pairCounts[word_pair] / self.counts[word0] # P(Word0 | word pair)
        p2 = self.counts[word1] / self.total
        probability = (1 - self.lambda1) * p1 + self.lambda1 * (1 - self.lambda2) * p2
        return probability

    def getSentenceProbability(self, sen):
        prob_found = 0
        is_first = True
        for idx, word in enumerate(sen):
            if idx != 0:
                if is_first:
                    prob_found = self.prob((sen[idx-1], word))
                    is_first = False
                else:
                    prob_found *= self.prob((sen[idx-1], word))
        return prob_found

    def generateSentence(self):
        init_word = start
        final_sentence = []
        final_sentence.append(init_word)
        while init_word != end:
            next_options = [word for word in self.counts.keys() if (init_word, word) in self.pairCounts.keys()]
            selected_option = random.choice(next_options)
            init_word = selected_option
            final_sentence.append(init_word)
        return final_sentence

    def getCorpusPerplexity(self, test_corpus):
        words_num = 0
        perplex = 0
        for each_sentence in test_corpus:
            words_num += len(each_sentence)
            prob_found = self.getSentenceProbability(each_sentence)
            if prob_found > 0:
                perplex += math.log(prob_found, 2)
        perplexity = 2**((-1/words_num) * perplex)
        return perplexity

    def generate_sentence_bgli(self):
        sen = self.generateSentence()
        prob = self.getSentenceProbability(sen)

        sentence_generated = str(prob) + " " + " ".join(sen) 
        print("bigram linear Interpol:\n", sentence_generated)

    def generateSentencesToFile(self, numberOfSentences, filename):
        print("writing file," , filename)
        filePointer = open(filename, 'w+')
        
        for i in range(0,numberOfSentences):
            
            sen = self.generateSentence()
            prob = self.getSentenceProbability(sen)

            stringGenerated = str(prob) + " " + " ".join(sen) 
            print(stringGenerated, end="\n", file=filePointer)
 
class UnigramDist:
    def __init__(self, corpus):
        self.counts = defaultdict(float)
        self.total = 0.0
        self.train(corpus)
    #endddef

    # Add observed counts from corpus to the distribution
    def train(self, corpus):
        for sen in corpus:
            for word in sen:
                if word == start:
                    continue
                self.counts[word] += 1.0
                self.total += 1.0
            #endfor
        #endfor
    #enddef

    # Returns the probability of word in the distribution
    def prob(self, word):
        return self.counts[word]/self.total
    #enddef

    # Generate a single random word according to the distribution
    def draw(self):
        rand = random.random()
        for word in self.counts.keys():
            rand -= self.prob(word)
            if rand <= 0.0:
                return word
	    #endif
	#endfor
    #enddef
#endclass

#-------------------------------------------
# Functions
#-------------------------------------------

def make_vocabulary(corpus):
    
    vocab_set = set()

    for sentences in corpus:
        for word in sentences:
            if word not in vocab_set:
                vocab_set.add(word)
    
    return vocab_set

#-------------------------------------------
# The main routine
#-------------------------------------------
if __name__ == "__main__":
    #read your corpora
    trainCorpus = readFileToCorpus('train.txt')
    trainCorpus = preprocess(trainCorpus)
    
    posTestCorpus = readFileToCorpus('pos_test.txt')
    negTestCorpus = readFileToCorpus('neg_test.txt')
    
    vocab = set()
    vocab = make_vocabulary(trainCorpus)

    posTestCorpus = preprocessTest(vocab, posTestCorpus)
    negTestCorpus = preprocessTest(vocab, negTestCorpus)

#    Run sample unigram dist code
    # unigramDist = UnigramDist(trainCorpus)
    # print("Sample UnigramDist output:")
    # print("Probability of \"picture\": ", unigramDist.prob("picture"))
    # print("\"Random\" draw: ", unigramDist.draw())
    
    unigramModel = UnigramModel(trainCorpus,posTestCorpus)
    
    print("Perplexity:")
    print("Unsmoothed Unigram(negative corpus)",unigramModel.getCorpusPerplexity(negTestCorpus))
    print("Unsmoothed Unigram(Positive corpus)",unigramModel.getCorpusPerplexity(posTestCorpus))

    Smoothed_unigram_Model = SmoothedUnigramModel(trainCorpus,vocab,posTestCorpus)
    
    print("Smoothed Unigram(negative corpus)",Smoothed_unigram_Model.getCorpusPerplexity(negTestCorpus))
    print("Smoothed Unigram(Positive corpus)",Smoothed_unigram_Model.getCorpusPerplexity(posTestCorpus))

   
    bigramModel = BigramModel(trainCorpus, vocab,posTestCorpus)
    print("Unsmoothed Bigram(negative corpus)",bigramModel.getCorpusPerplexity(negTestCorpus))
    print("Unsmoothed Bigram(Positive corpus)",bigramModel.getCorpusPerplexity(posTestCorpus))
    

    bgm_li = LinearInterpolationModel(trainCorpus,vocab,posTestCorpus)
    print("Smoothed_li Bigram(negative corpus)",bgm_li.getCorpusPerplexity(negTestCorpus))
    print("Smoothed_li Bigram(Positive corpus)",bgm_li.getCorpusPerplexity(posTestCorpus))

    print("writing in files")
    unigramModel.generateSentencesToFile(20,"unigram_output.txt")
    Smoothed_unigram_Model.generateSentencesToFile(20,"smooth_unigram_output.txt")
    bigramModel.generateSentencesToFile(20,"bigram_output.txt")
    bgm_li.generateSentencesToFile(20,"smooth_bigram_output.txt")
    

#                                   PERPLEXITY 
#Model 	            Negative test corpus	Positive test corpus
#Unigram	             475	                     493
#Smoothed Unigram	     478	                     495
#Bigram	                 478.24	                     495.30
#Unsmoothed Bigram	     1107	                    1087
#Linear Bigram	         263	                     255


## QUESTION : PERPLEXITY
#As you can see, the linear bigram model has the lowest perplexity for both the negative and positive test corpora. 
# This means that the linear bigram model is able to predict the words in the test corpora better than the other models.

#There is a difference in perplexity between the two test corpora for all of the models except the unsmoothed bigram model. 
# The negative test corpus has a higher perplexity than the positive test corpus for all of the other models.
#  This suggests that the language models are better at predicting the words in the positive test corpus than 
# the words in the negative test corpus.

## QUESTIONS:
## Q.1: LENGTH

#The length of unigram model is controlled by adding words of higher probability randomly until end of sentence is found. 
#for bigram model length is controlled by the probabilities of the next word based on previous word until sentence end reaches.

## Q.2: GENERATED SENTENCE EVAL BASED ON PROBABILITY

# The models give diffrent probabilities to diffrent sentences, this is because
# in these models probability is used to make a sentence and not context.

# In Unsmothed bigram ,there is alot of words which have 0 probability,therefore it has high perplexity whereas for 
#For Smoothed Bigram with Linear Interpolation smoothing the results are better as each word has non - zero probability.

## Q.3: Additional sentences

#Smoothed:  great animated vocal performer who belongs to accomplished , such ghastly visions and deliverance
# Unsmoothed: 10-year-old angst brook's performer eccentricities metro blackness invested cardinal bribes

# In these extracted texts, the Smoothed Bigram is better as it assigns non zero probability to all words, making it 
# a good model.

## Q.4: Perplexity by test corpus

#For each of the four models, the test corpus with the higher perplexity is the positive test corpus.
#  This is because the positive test corpus is more different from the training corpus than the negative test corpus.
#  The training corpus contains words or word pairs that are found mostly in negative test corpus
# , so the models are better at predicting the words in the 
# negative test corpus than the words in the positive test corpus.
