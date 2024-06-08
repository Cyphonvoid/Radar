import spacy
nlp = spacy.load("en_core_web_sm")
import en_core_web_sm
nlp = en_core_web_sm.load()

class Vector():

    def __init__(self):
        self.nlp = nlp
        self.__word = None
        self.__second_word = None
    
    def word(self, text):
        self.__word = text
        return self
    
    def similar_to(self, text):
        self.__second_word = text        
        obj1 = self.nlp.vocab[self.__word]
        obj2 = self.nlp.vocab[self.__second_word]
        score = obj1.similarity(obj2)
        return score
    

vector = Vector()
score = vector.word("Red").similar_to("yellow")
print(score)