import requests
import time

class OllamaApi():

    def __init__(self) -> None:
        self.url = "http://localhost:11434/api/generate -d "
        self.headers = {
            "model":"None",
            "prompt":"",
            "stream":False
        }

        self.url = ""
        self.methods = []

    def select_model(self, model_name):
        self.headers["model"] = model_name
    
    def __safety_check(self):
        return (self.headers["model"] != "None")
    
    def ask(self, data):
        if(self.__safety_check() == False): 
            print("OllamaAPI: Please specify model name")
            return None
        try:
            data = requests.get(self.url, headers=self.headers)
            return data.json()["response"]
        except:
            print("Couldn't generate response")