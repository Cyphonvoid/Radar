from ai import *


class Type():
    TEXT = 'Text'
    IMAGE = 'Image'
    BASE = 'Base'
    LIST = [TEXT, IMAGE, BASE]

class BaseDocument():

    def __init__(self):
        self.__document_type = Type.BASE
    
    def Type(self):
        return self.__document_type
    
    def InsertContent(self, content):
        pass

    def Get(self):
        pass

class ImageVecDocument(BaseDocument):

    def __init__(self):
        super().__init__()
        self.__document_type = Type.IMAGE


class TextVecDocument(BaseDocument):

    def __init__(self):
        super().__init__()
        self.__document_type = Type.TEXT
        self.__base_doc_template = {
            'description':None,
            'description_embedding':None
        }
    
    def InsertContent(self, content):
        #This map allows the swap/map some keys to self.__base_doc_template keys for eg mapping 'content' field of map1 to 'description' field of map2
        key_map = {
            'content':'description'
        }
        Key = None
        for key, value in content.items():
            try:Key = key_map[key]
            except:Key = key
            self.__base_doc_template[Key] = value

        description = self.__base_doc_template['description']
        if(description != None):
            embedding = HUG_FACE.GetEmbedding(description)
            #If embedding api not working then do this.
            if(embedding == None):
                self.__base_doc_template['description_embedding'] = "Embedding API not returning embedding"
                return
            self.__base_doc_template['description_embedding'] = embedding

    def Get(self):
        return self.__base_doc_template