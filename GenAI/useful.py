from ai import *


class DocumentTranslator():

    def __init__(self):
        self._document_list = None
        self._open_visual_api = OpenVisualAI()
    
    def save_mongo_documents(self, list):
        self._document_list = list

    def convert_and_transfer(self):
        listings = self._document_list
        #Processing and putting processed vector documents into new OpenVisualAI database
        for listing in listings:
            vector_document = self._open_visual_api.translate(listing)
            if(vector_document == False): continue

            response = self._open_visual_api.addListing(vector_document)
            if(response == False):
                print(listing, "\x1b[31mcouldn't add this listing\x1b[0m")

    def test(self):
        listings = self._document_list
        for listing in listings:
            vector_document = self._open_visual_api.translate(listing)
            print(vector_document)



translator = DocumentTranslator()

#Pulled listings from regular OpenVisualDB database
listing = Listing()
listings = listing.InCountry("USA").InState("California").InCity("National City").Get()

translator.save_mongo_documents(listings)

#translator.test()
translator.convert_and_transfer()