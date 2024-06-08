from flask import Flask, request
import json
from ai import *
from flask_cors import CORS

app = Flask(__name__)
CORS(app, origins=['http://localhost:3000'])


llm = QueryRouter()
llm.selectModule('OpenVisualLLM')

@app.route("/")
def Root():
    return "AI Server is running..."


@app.route("/chat", methods=["POST", "GET"])
def AskOllamaLLM():
    response = llm.respondOn(request.get_json()["User"])
    final_response = {
        'AI':response
    }
    return final_response


#FLASK CONFIGURED WITH GUNICORN
#WSGI IP PORT = 0.0.0.0 FOR EXTERNAL ACCESS
if __name__ == "__main__":
    print("entered wsgi.py ....")
    print("app is running")
    app.run(host='0.0.0.0', port=9999)




