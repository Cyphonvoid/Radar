import pymongo
import requests
import time
import copy
import json
from utility import Flag
import ollama

uri = "mongodb+srv://yashaswikul:yash18hema06@cluster0.vktjrwl.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"

class MongoDatabase():

    def __init__(self, connection_string):
        self.string = connection_string
        self.ready = False
        self.client = None

        if(isinstance(connection_string, str) == True):
            self.client = pymongo.MongoClient(self.string)
            self.ready = True

    def __status(self):
        return (self.ready == True and self.client != None)
    
    def GetDatabase(self, database):
        if(self.__status() == False):
            return None
        return self.client.get_database(database)


class HUG_FACE():

    MODEL_ID = "sentence-transformers/all-MiniLM-L6-v2"
    TOKEN = "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"
    URL = "https://api-inference.huggingface.co/pipeline/feature-extraction/" + MODEL_ID

    def UseToken(token):
        HUG_FACE.TOKEN = token

    def GetEmbedding(text):
        try:
            text = [text]
            response = requests.post(
                url=HUG_FACE.URL,
                headers = {"Authorization": f"Bearer {HUG_FACE.TOKEN}"},
                json={"inputs": text}
            )

            result = response.json()[0]
            if(isinstance(result, list) == True):
                return result
            return False

        except Exception as error:
            print(error)
    
    def GetEmbedding2(text) -> list[float]:
        try:
            if(isinstance(text, list) == False):
                text = [text]
            response = requests.post(
                url=HUG_FACE.URL,
                headers = {"Authorization": f"Bearer {HUG_FACE.TOKEN}"},
                json={"inputs": text}
            )

            return response.json()
        except Exception as error:
            print(error)
            return None


class ListingDescription():

    def __init__(self):
        self.properties = {
            'address':"None",
            'type':"None",
            'state':"None",
            'zipcode':"None",
            'country':"None",
            'city':"None",
            'price':"None",
            'beds':"None",
            'baths':"None",
            'area':"None",
            'category':"None"
        }

    def __reset_properties(self):
        for key in self.properties.keys():
            self.properties[key] = "None"
    
    def __properties_empty(self):
        for key in self.properties.keys():
            if(self.properties[key] != "None"): return False    
        return True
    
    def createTemplate(self, properties):
        #Reset the properties
        if(self.__properties_empty()==False):self.__reset_properties()

        #Set the valid properties 
        for key, value in properties.items():
            try: self.properties[key] = value
            except Exception as error: pass
        
    def toText(self):
        #NOTE:
        #May need to optimize it since uneccesary use of language may affect over overall meaning of embeddings.
        #Address, city, state, country
        geography = "Property is located at " + self.properties['address'] + ", " + self.properties['city'] + ", " + self.properties['state'] + " " + self.properties['zipcode']
        #price, type
        price = " Property has a price of " + self.properties['price'] + " dollars "
        if(self.properties['type'] == "For rent"): price += " per month"
        #beds, bath
        interior = "Property has " + self.properties['beds'] + " beds, " + self.properties['baths'] + " baths "
        #area
        area = "Property is " + self.properties['area'] + "sq ft "
        #category
        category = "Property is a " + self.properties['category'] + " "
        return geography + price + interior + area + category


class VectorEncoder():
     
    def __init__(self) -> None:
        pass

    def encode(self, data):
        #Convert the data to embeddings
        return HUG_FACE.GetEmbedding(data)
    
    def decode(self, embedding):
        #Given embedding convert it to real data
        pass


class Listing():

    URI = "mongodb+srv://yashaswikul:yash18hema06@cluster0.vktjrwl.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"
    def __init__(self):
        self.cluster = MongoDatabase(Listing.URI)
        self.database = self.cluster.GetDatabase("OpenVisualDB")

        self.path = {
            'country':"",
            'state':"",
            'city':""
        }
    
    def InState(self, state):
        self.path['state'] = state
        return self
    
    def InCity(self, city):
        self.path['city'] = city
        return self
    
    def InCountry(self, country):
        self.path['country'] = country
        return self

    def Get(self):
        path = self.path['country'] + "/" + self.path['state'] + "/" + self.path['city']
        collection = self.database.get_collection(path)
        list = []
        #Return all the documents within the collection in json format
        cursor = collection.find({})
        try:
            while(True):
                doc = cursor.next()
                list.append(doc)
                #time.sleep(0.1)
        except StopIteration as error:
            print(error, "reached the end of the documents")
        return list



class VectorDocument():
    #Document for when pulling vector documents from mongodb
    def __init__(self, score, content, embedding):
        
        self.fields = {
            'score':score,
            'content':content,
            'embedding':embedding
        }

    def Print(self, value='all'):
        if(value == 'all'):
            print(self.fields['score'], self.fields['content'], self.fields['embedding'])
        
        if(value in self.fields.keys()):
            print(self.fields[value])

    def SetScore(self, value):
        self.fields['score'] = value
    
    def SetContent(self, value):
        self.fields['content'] = value

    def SetEmbedding(self, value):
        self.fields['embedding'] = value

    def GetScore(self):
        return self.fields['score']

    def GetContent(self):
        return self.fields['content']
    
    def GetEmbedding(self):
        return self.fields['embedding']


class OpenVisualAI():

    def __init__(self):
        self.cluster = MongoDatabase(uri)
        self.database = self.cluster.GetDatabase("OpenVisualAI")
        self.collection = self.database.get_collection("Listings")
        
        self.aggregration_settings = { 
            "$vectorSearch":{
                "queryVector":"",
                "path":"description_embedding",
                "numCandidates":100,
                "limit":1,
                "index":"description_index"
            }
        }

        self.template = {
            "address":"None",
            "description":"None",
            "description_embedding":"None"
        }
    

    def translate(self, listing):
        #Get all the valid fields within listing
        template = {
            'address':listing['Address'],
            'type':listing['Filters']['Filter Settings']['Payment Type'],
            'zipcode':listing['ZipCode'],
            'state':listing['State'],
            'country':"USA",
            'city':listing['City'],
            'price':listing['Price'],
            'beds':"unknown",
            'baths':"unkown",
            'area':listing['Stats'][3],
            'category':"Condo/House"
        }

        #Create a description template using these fields
        description = ListingDescription()
        description.createTemplate(template)

        #Convert them to totext()
        text_data = description.toText()

        #create by using text as description and it's embedding as description_embedding
        embedding = HUG_FACE.GetEmbedding(text_data)

        if(embedding == False):
            return False
    
        ai_template = {
            'address':template['address']+", "+template['city']+", "+template['state']+" "+listing['ZipCode'],
            'description':text_data,
            'description_embedding':embedding
        }

        return ai_template

    def searchDescription(self, data):

        #VectorSearch aggregration pipeline preparation
        content = copy.copy(self.aggregration_settings)
        embedding = HUG_FACE.GetEmbedding(data)
        content['$vectorSearch']['queryVector'] = embedding

        #NOTE Since $vectorSearch not working, we've have to use regular $search pipeline
        command_cursor = self.collection.aggregate([
            {
                "$search": {
                "index": "description_index",
                "text": {
                    "query": data,
                    "path": {
                        "wildcard": "*"
                        }
                    }
                }
            },
            {
                "$project": {
                "description": 1,
                "description_embedding":1, 
                "score": { "$meta": "searchScore" } 
                }
            }
        ])

    
        doc_list = []
        for doc in command_cursor:
            doc_list.append(VectorDocument(doc['score'], doc["description"], doc['description_embedding']))
        
        return doc_list

    def addListing(self, listing):
        document = copy.copy(self.template)
        for key, value in listing.items():
            try: document[key] = value
            except Exception:pass

        value = self.collection.insert_one(document)
        return value
    
    def addCustomDocument(self, Document):
        value = self.collection.insert_one(Document)
        return value

    def deleteListing(self, address):
        addr_map = {"address":address}
        value = self.collection.find_one_and_delete(addr_map, {"$set":value})
        return value != None


class ContextProcessor():

    def __init__(self) -> None:
        pass


class OllamaApi():

    def __init__(self) -> None:
        self.url = "http://localhost:11434/api/generate -d "
        self.model = "llama3"
        self.headers = {
            "model":self.model,
            "prompt":"",
            "stream":False
        }
        self.url = ""
        self.methods = []
        self.messages = []

    def select_model(self, model_name):
        self.headers["model"] = model_name
    
    def __safety_check(self):
        return (self.headers["model"] != "None")
    
    def ask2(self, data):
        if(self.__safety_check() == False): 
            print("OllamaAPI: Please specify model name")
            return None
        try:
            data = requests.get(self.url, headers=self.headers)
            return data.json()["response"]
        except:
            print("Couldn't generate response")

    def ask(self, data):
        #Chat mode
        self.messages.append({'role':'user', 'content':data})

        #Can adjust the context info based on relevancy
        relevant_last_message = -5 #Means last four indexes 
        return ollama.chat(model=self.model, messages=self.messages[relevant_last_message:])['message']['content']

        #Generate mode
        return ollama.generate(model='llama2', prompt=data)['response']
        
    
class RetrieverComponent():

    def __init__(self):
        self.module_object = None
        self.flag = Flag(False)

    def Connect(self, component):
        self.module_object = component

    def Get(self):
        return self.module_object
    
    def Status(self):
        return self.flag.check()


class LLMInterfaceComponent():

    def __init__(self):
        self.module_object = None
        self.flag = Flag(False)
    
    def Connect(self, component):
        self.module_object = component
    
    def Get(self):
        return self.module_object

    def Status(self):
        return self.flag.check()


class SystemPrompt():

    def __init__(self):
        self.__user_query = "None"
        self.__retrieved_docs = "None"
        self.__final_prompt = ""
        self.__template = """You will answer questions based on data provided from your database. Answer only using the data provided.
        """
    def __create_final_prompt(self):
        
        prompt = self.__template
        context = "Database Info: " + self.__retrieved_docs
        question = "Question: " + self.__user_query

        prompt += context + question

        self.__final_prompt = prompt

        return self.__final_prompt
    
    def setPromptTemplate(self, template):
        self.__template = template

    def storeUserQuery(self, query):
        self.__user_query = query

    def storeRetrievedDocs(self, docs):
        self.__retrieved_docs = docs

    def GetfinalPrompt(self):
        return self.__create_final_prompt()

    def deletePrompt(self):
        self.__user_query = "None"
        self.__retrieved_docs = "None"
        self.__final_prompt = "None"


class OpenVisualLLM():
    """
    OpenVisualLLM component implements RAG Architecture to allow Ollama LLM model to communicate with mongodb vector database
    to produce most accurate responses. Database contains vectorized information about rental listing information which is contextualized as a part
    and then fed into Ollama LLM using SystemPrompt() class to produce response which is then returned to orginal user.

    KnowledgeBase: Component representing a vector database for vectorized information retrieval
    LLM Interface: Component represeting a LLM like ollama which will consume incoming data from vector database
    """

    def __init__(self):
        self.__knowledge_base_retriever = RetrieverComponent()
        self.__llm_interface_module = LLMInterfaceComponent()

        self.__knowledge_base_retriever.Connect(OpenVisualAI())
        self.__llm_interface_module.Connect(OllamaApi())

        self.__user_prompt = ""
        self.__retrieved_data = ""

    def __generate_response(self):
        #Use user query and retrieve related documents first
        self.__retrieved_data = self.KnowledgeBase().Get().searchDescription(self.__user_prompt)
        
        #Formulate a response if there's no information available
        if(len(self.__retrieved_data) == 0):
            self.__retrieved_data.append("No information")
            print("\nRetrieved info....", self.__retrieved_data[0], "\x1b[31m OpenVisualAI database results:- No relevant sources [OpenVisualLLM instance] \x1b[0m \n\n")
            #prompt = SystemPrompt()
            #prompt.storeUserQuery(self.__user_prompt)
            #prompt.storeRetrievedDocs(self.__retrieved_data[0])
            print(self.__user_prompt, " this is userprompt line 458")
            return self.__llm_interface_module.Get().ask(self.__user_prompt)
       
    
        self.__retrieved_data = self.__retrieved_data[0]
        score = self.__retrieved_data.GetScore()
        content = self.__retrieved_data.GetContent()
        print("\nRetrieved info... SCORE =",score, content, "\x1b[33m Source:- OpenVisualAI database [OpenVisualLLM instance] \x1b[0m \n\n")

        #Check how relevant the score is even if documents are found    

        response = "No response ai.py"
        #If score is within range then it's usable information
        if(score >= 1 and score <= 100):
            system_prompt = SystemPrompt()
            system_prompt.storeUserQuery(self.__user_prompt)
            system_prompt.storeRetrievedDocs(self.__retrieved_data.GetContent())
            #Feed it to the A.I
            response = self.__llm_interface_module.Get().ask(system_prompt.GetfinalPrompt())
            return response
        
        #Otherwise if score is below the range then it's not usable information
        if(score < 1 and score >= 0):
            #neg_prompt = SystemPrompt()
            #neg_prompt.setPromptTemplate("")
            #neg_prompt.storeUserQuery(self.__user_prompt)
            #neg_prompt.storeRetrievedDocs("No information available about this query")
            #response = self.__llm_interface_module.Get().ask(neg_prompt.GetfinalPrompt())
            response = self.__llm_interface_module.Get().ask(self.__user_prompt)
            return response
        
        return response
    
    def LLM(self):
        return self.__llm_interface_module
    
    def KnowledgeBase(self):
        return self.__knowledge_base_retriever
    
    def inputPrompt(self, prompt):
        self.__user_prompt = prompt
        return self.__generate_response()


class QueryRouter():

    def __init__(self):
        self.modules = {
            'OpenVisualLLM':OpenVisualLLM(),
            'OpenVisualAI':OpenVisualAI(),
            'OllamaApi':OllamaApi()
        }

        self.functions = {
            'OpenVisualLLM':self.modules['OpenVisualLLM'].inputPrompt,
            'OpenVisualAI':self.modules['OpenVisualAI'].searchDescription,
            'OllamaApi':self.modules['OllamaApi'].ask
        }

        self.current_module = None
    
    def selectModule(self, name):
        self.current_module = name
    
    def respondOn(self, prompt):
        try:
            response = self.functions[self.current_module](prompt)
            return response
        except Exception as error:
            print(error, self.current_module, " object doesn't exist")
            time.sleep(2)
