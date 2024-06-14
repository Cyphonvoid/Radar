from ai import *
from VectorDB import *
import requests
import time
import threading
import datetime

#RadarServer uses NodeMCU WebServer API to feed data into RAG Based AI infrastructure
class RadarServer():

    def __init__(self):
        self._nodemcu_webserver = "http://webserver/radarStatus"
        self._OpenVisualApi = OpenVisualAI()
        self._response_stack = []
        self._response_stack_thread = None
    
    def start_listening(self):
        #Constantly make request to the url endpoint to get the radar data
        while(True):
            response = requests.get(self._nodemcu_webserver)
            if(response.status_code == 200):
                content = response.json()

                #Create a document to store information about detection only if object has been detected.
                if(content['detected'] == True):
                    current_time = datetime.datetime.now()
                    content = "[AI Radar] Motion detection detected object at " + content['distance'] + " cm "
                    content += " at time " + current_time
                    document = TextVecDocument()
                    document.InsertContent({'content':content, 'type':'Text'})
                    self._response_stack.append(document)
            else:
                self._response = ""
            time.sleep(10)

    def store_responses(self):
        #Store the responses into mongoDB collection defined within OpenVisualAI Api
        while(True):
            if(len(self._response_stack) == 0):
                document = self._response_stack[0]
                response = self._OpenVisualApi.addCustomDocument(document.Get())
                self._response_stack.pop(0)
            
            time.sleep(10)
    
    def start_stack_thread(self):
        #Start the thread to process response buffer to upload the documents directly to AI Vector Database
        self._response_stack_thread = threading.Thread()
        self._response_stack_thread.start(self.store_responses)

    def run(self):
        #Main function to initiate all functionalities
        self.start_stack_thread()
        self.start_listening()


Server = RadarServer()
Server.run()