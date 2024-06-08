from ai import *
from VectorDB import *


class Console():

    Router = QueryRouter()
    Router.selectModule('OpenVisualLLM')
    #Router.selectModule('OllamaApi')

    def __init__(self):

        self.functionalities = {
            'Search':self.__search,
            'Chat':self.__chat,
            'upload':self.__upload
        }


    def AddCommand(self, command, function):
        self.functionalities[command] = function
    
    def __upload(self):
        def text_doc(): return TextVecDocument()
        def image_doc(): return ImageVecDocument()
        get_doc = {
            'Text':text_doc,
            'Image':image_doc
        }
        document = None

        while(True):
            print("Select Documnent type", Type.LIST, end="")
            type = input()
            
            if(type == "exit"):
                return
            
            try: document = get_doc[type]()
            except:
                print("Selected Wrong Document type")
                input()
                continue

            print("Enter content to put into document: ", end="")
            content = input()
            document.InsertContent({'content':content, 'type':'Text'})
            OpenVisualApi = OpenVisualAI()
            response = OpenVisualApi.addCustomDocument(document.Get())
            print("Response", response)
            y = input()
            break

    def __search(self):

        print("-:Semantic Search:-")
        print("Type your text for query: ", end="")
        text = input()

        if(text == "exit"):
            return
    
        print("Querying... ", end="")
        data = Console.Router.respondOn(text)
        print(data)

        y = input()


    def __chat(self):
        print("-:Ollama LLM Chat:-\n")
        while(True):
            print("User: ", end="")
            text = input()

            if(text == "exit"):
                break

            print("Ollama: ", end="")
            data = Console.Router.respondOn(text)
            print(data)
            print("\n\n")
        

    def headings(self):
        print("Console is running....")
        print("Commands: [", end="")
        keys = self.functionalities.keys()
        count = 0
        for command in keys:
            if(count >= len(keys)-1):
                print(command, end="")
                break
            print(command, end=", ")
            count+=1

        print("]")
        print("_"*40, end="")
        print("\n")


    def run(self):

        while(True):
            self.headings()
            value = input()
            if(value == "exit"):break
            try: self.functionalities[value]()
            except Exception as error: pass
            print("\033[0;0H")
            print("\033[J")
        return


console = Console()
console.run()
