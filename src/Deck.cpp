#include "Deck.h"

Deck::Deck() {}

void Deck::loadDeckFromJSONFile(std::string filepath)
{
    // load the cards from the jsonlines file
    std::fstream jsonfile;
    jsonfile.open(filepath);
    if (jsonfile.is_open())
    {
        //  initialize a string to hold the lines
        std::string line;

        // get the header data
        std::getline(jsonfile, line); // get the header line
        json jsondata = json::parse(line);
        this->factor = jsondata.at("factor");
        this->decay = jsondata.at("decay");
        std::vector<float> params_in = jsondata.at("params");
        this->params = params_in;

        // initialize the cards
        while (std::getline(jsonfile, line))
        {
            json jsondata = json::parse(line);
            int cardID = jsondata.at("cardID");
            int initalized = jsondata.at("initialized");
            float stability = jsondata.at("stability");
            float difficulty = jsondata.at("difficulty");
            std::cout << json::parse(line) << '\n';

            // add the card to the appropriate container
            if (initalized){
                std::string lastReviewTimeUTCStr = jsondata.at("lastReviewTimeUTC");
                Card card = Card(this->params, this->factor, this->decay, cardID, lastReviewTimeUTCStr, stability, difficulty, true);
                std::cout << "Adding card to initialized ordered set" << std::endl;
                this->reviewNext.insert(card);
            }
            else{
                Card card = Card(this->params, this->factor, this->decay, cardID, false);
                std::cout << "Adding card to new cards queue" << std::endl;
                this->newCards.push(card);
            }
            
        }
        jsonfile.close();
        this->numCards = this->newCards.size();
    }
}

void Deck::printDeck()
{
    if (this->reviewNext.size() > 0){
        // print the initialized cards
        for (auto card : this->reviewNext)
        {
            card.printCard();
            std::cout << std::endl;
        }
    }
    
    if (this->newCards.size() > 0){
        // print the uninitialized cards
        std::queue<Card> tmpNewCards;
        Card tmpCard;
        while (!this->newCards.empty()){
            tmpCard = this->newCards.front();
            this->newCards.pop();
            tmpCard.printCard();
            std::cout << std::endl;
            tmpNewCards.push(tmpCard);
        }

        // add the cards back to the queue
        while (!tmpNewCards.empty()){
            this->newCards.push(tmpNewCards.front());
            tmpNewCards.pop();
        }
    }
    
}

void Deck::writeDeckToFile(std::string filepath)
{
    std::ofstream outfile; 
    outfile.open(filepath);
    if (outfile.is_open())
    {
        // write the header
        json jsonheader = {
            {"decay", this->decay},
            {"factor", this->factor},
            {"params", this->params}
        };
        outfile << jsonheader;
        outfile << "\n";

        // write the initialized cards first
        for (auto card : this->reviewNext)
        {
            outfile << card.asJSON();
            outfile << "\n";
        }

        // write the uninitialized cards
        std::queue<Card> tmpNewCards;
        Card tmpCard;
        while (!this->newCards.empty()){
            tmpCard = this->newCards.front();
            this->newCards.pop();
            outfile << tmpCard.asJSON();
            outfile << "\n";
            tmpNewCards.push(tmpCard);
        }

        // add the cards back to the queue
        while (!tmpNewCards.empty()){
            this->newCards.push(tmpNewCards.front());
            tmpNewCards.pop();
        }
    }
    outfile.close();  
}

Card Deck::getNextReviewCard()
{
    if (reviewNext.size() > 0){
        return *(this->reviewNext.begin());
    }   
    else{
        return newCards.front();
    }
}

Card Deck::drawCard()
{
    Card nextCard;
    if (this->reviewNext.size() > 0 ){
        std::cout << "Checking reviewNext to see if any cards are due." << std::endl;
        // get the current UTC time to compare to time in next card
        time_t currentTime = time(0);
        tm *gmtm = gmtime(&currentTime);
        currentTime = mktime(gmtm);
        
        // get the time in the next card
        nextCard = *(this->reviewNext.begin());
        time_t nextTime = mktime(nextCard.getDueDate());
        if (difftime(currentTime, nextTime) > 0){
            std::cout << "A card is due." << std::endl;
            this->reviewNext.erase(this->reviewNext.begin());
            return nextCard;
        }
        std::cout << "No cards are due." << std::endl;
    }
    std::cout << "newCards empty: " << this->newCards.empty() << std::endl;
    if (!this->newCards.empty()){
        std::cout << "Getting a new card." << std::endl;
        nextCard = this->newCards.front();
        std::cout << "Popping." << std::endl;
        this->newCards.pop();
        return nextCard;
    }
    std::cout << "no cards in newCards either." << std::endl;

    // return a dummy card if there are no cards in either deck
    // to-do: replace this with something more sensical
    std::vector<float> params(17, -1);
    return Card(params, -1, -1, -1, false);
}

void Deck::registerReview(Card card)
{
    this->reviewNext.insert(card);
}