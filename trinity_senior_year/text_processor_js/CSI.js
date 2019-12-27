
//global variables for tabs
var tabs = {};
var tabName = "x";
var tabNumber = 1;

//Setup
function setup() {

  noCanvas();

  createFileInput(gotFile, 'multiple').parent("top");
}

//main function, called when newfile is loaded
function analyzeText(loadedFile, tabID){

//variables for each text
var sentenceCount = 0;
var wordCount = 0;
var charsWhite = 0;
var charsNoWhite = 0;
var charsAlphaNum = 0;

var sentences = [];
var firstLetterSentence = 0;

var wordLengths = [];
var avgWordLength = 0;
var avgSentenceCharsLength = 0;
var longestWord = "";

var words = {};
var txt = loadedFile.data;

//Removes special cases
txt = txt.replace(/Mr./g, "Mr");
txt = txt.replace(/Mrs./g, "Mrs");
txt = txt.replace(/Ms./g, "Ms");
txt = txt.replace(/\r?\n|\r/g, " ");

txt = txt.replace(/--/g, " ");
txt = txt.replace(/-/g, " ");
txt = txt.replace(/_/g, "");


//runs through each character
for(var i = 0; i<txt.length; i++){

//If character is punctuation, count as sentence
 if(txt.charCodeAt(i) == 63 || txt.charCodeAt(i) == 33 || txt.charCodeAt(i) == 46){
        sentences.push(txt.slice(firstLetterSentence, i+1));
        firstLetterSentence = i+2;
        sentenceCount += 1;
      }

    
  }

  //Runs through sentences and counts sentence length
  for(var x = 0; x<sentences.length; x++){
    avgSentenceCharsLength += sentences[x].length;
  
  }
  avgSentenceCharsLength = round(avgSentenceCharsLength / sentences.length * 100) / 100;



  txt = sentences.join(" ");
  var tokens = txt.split(' ');// split by whitespace


//Runs through each word
for(var c = 0; c<tokens.length; c++){
  var lowerCaseWord = tokens[c].toLowerCase();

  //If last character is alphanumerical
    if(tokens[c].charCodeAt(tokens[c].length-1) <= 90 && tokens[c].charCodeAt(tokens[c].length-1) >= 65 || tokens[c].charCodeAt(tokens[c].length-1) >= 97 && tokens[c].charCodeAt(tokens[c].length-1) <= 122){
       
        //Checks to see if word is already in word object
          if(words[lowerCaseWord] === undefined)
          {
            isInWords = false;
             words[lowerCaseWord] = 1;
          }

          else
          {
            words[lowerCaseWord] += 1;
          }

      //Counts word lengths
      wordLengths.push(tokens[c].length);

      //Tracks longest word
      if(tokens[c].length > longestWord.length)
      {
        longestWord = tokens[c];
      }
    }

  //If character is not alphannumerical
    else
    {

      //Checks to see if word is already in word object
          if(words[lowerCaseWord.slice(0, lowerCaseWord.length-1)] === undefined)
          {
            isInWords = false;
             words[lowerCaseWord.slice(0, lowerCaseWord.length-1)] = 1;
          }

          else
          {
           
            words[lowerCaseWord.slice(0, lowerCaseWord.length-1)] += 1;
          }

      //Counts word lengths
      wordLengths.push(tokens[c].length-1);

      //Tracks longest word
      if((tokens[c].length - 1) > longestWord.length)
      {
        longestWord = tokens[c].substring(0, tokens[c].length-1);
      }
    }
  }


//gets avg word length
  for(var n = 0; n<wordLengths.length; n++){

    avgWordLength += wordLengths[n];
  }
  avgWordLength = avgWordLength / wordLengths.length;
  avgWordLength = round(avgWordLength*100)/100;


//Runs through each word
for(var a = 0; a<tokens.length; a++){

//Runs through each leter in each word and counts alphanums
    for(var b = 0; b<tokens[a].length; b++){
      charsNoWhite += 1;
        if(tokens[a].charCodeAt(b) <= 90 && tokens[a].charCodeAt(b) >= 65 || tokens[a].charCodeAt(b) >= 97 && tokens[a].charCodeAt(b) <= 122){
          charsAlphaNum += 1;
        }
      }
}

wordCount = tokens.length;



var wordsArray =[];
var wordsNumArray = [];

//Adds words and occurences to table
for (var checkWord in words) {

  var addedWord = false;
      var wordsArrayLength = wordsArray.length;


if(checkWord.length == 0)
{
  addedWord = true;
}

//Removes special cases
checkWord = checkWord.replace(/\r?\n|\r/g, "UHUH");
checkWord = checkWord.replace(String.fromCharCode(32), "UHUH");
      
//If word occurs only once
if(words[checkWord] === 1 && addedWord == false)
{

  addedWord = true;
  wordsArray.push(checkWord);
  wordsNumArray.push(words[checkWord]); 
}

    
      else
      {
          for(var i = 0; i < wordsArrayLength; i++)
          {
            //If checkWord occurs more than the word in array
            if(words[checkWord] > wordsNumArray[i] && addedWord == false)
            {
              addedWord = true;
            
              wordsArray.splice(i, 0, checkWord);
              wordsNumArray.splice(i, 0, words[checkWord]);
            }



          }

          //If word occurs less than all other words in array
          if(addedWord == false)
          {
            wordsArray.push(checkWord);
            wordsNumArray.push(words[checkWord]);
          }
      }
}

//RiTa No stops
var params = {
  ignoreStopWords: true, ignoreCase: true,
    ignorePunctuation: true
};

var wordsNoStops = RiTa.concordance(txt, params);



var wordsNoStopsArray = [];
var wordsNoStopsNums = [];

//RiTa no stops
for (var checkWord in wordsNoStops){

  var addedWord = false;
      var wordsArrayLength = wordsArray.length;


if(checkWord.length == 0)
{
  addedWord = true;
}


if(words[checkWord] === 1 && addedWord == false)
{
  //console.log(checkWord + " length is 1");

  addedWord = true;
  //console.log("1Adding " + checkWord + " : " + words[checkWord])
  wordsNoStopsArray.push(checkWord);
  wordsNoStopsNums.push(words[checkWord]); 
}

    
      else
      {
          for(var i = 0; i < wordsArrayLength; i++)
          {
            if(words[checkWord] > wordsNoStopsNums[i] && addedWord == false)
            {
             addedWord = true;
            
              wordsNoStopsArray.splice(i, 0, checkWord);
              wordsNoStopsNums.splice(i, 0, words[checkWord]);
            }

           
            

          }

          if(addedWord == false)
          {
            wordsArray.push(checkWord);
            wordsNoStopsNums.push(words[checkWord]);
          }
      }
    

}

//Table with stops
var table = "<table><tr><th>Words<br>(w/ Stop-word)</th><th>Occurences</th></tr>";
var tableNoStops = "<table><tr><th>Words<br>(w/o Stop-word)</th><th>Occurences</th></tr>";


var tableLength = 20;
var tableNoStopsLength = 20;
 
if(wordsArray.length < 20){
  tableLength = wordsArray.length;
}

if(wordsNoStopsArray.length<20){
  tableNoStopsLength = wordsNoStopsArray.length;
}
for(var i=0; i<tableNoStopsLength; i++){
  tableNoStops += ("<tr><td>"+wordsNoStopsArray[i]+"</td><td> "+round(wordsNoStopsNums[i]/wordCount*10000)/100+"%</td></tr>")
 
}
//tableLength = wordsArray.length;
for(var i = 0; i<tableLength; i++){

  
    table += ("<tr><td>"+wordsArray[i]+"</td><td> "+round(wordsNumArray[i]/wordCount*10000)/100+"%</td></tr>");

}

//Displays table
  table += "</table>";
  tableNoStops += "</table>";
 
  var tableDiv = createDiv(table).class(tabID).parent("left");
  var tableDiv2 = createDiv(tableNoStops).class(tabID).parent("left");

"<table><tr><th>Words<br>(w/o Stop-word)</th><th>Occurences</th></tr>";


//Tables with information
var sentenceTable = "<table>";

sentenceTable += "<tr><td>Sentences</td> <td>" + sentenceCount + "</td></tr>";
sentenceTable += "<tr><td>Average characters<br>per sentences</td> <td>" + avgSentenceCharsLength + "</td></tr>";
sentenceTable += "<tr><td>Average words<br>per sentence</td> <td>" + round(tokens.length/sentences.length * 100)/100 + "</td></tr>";
sentenceTable += "<tr><td>Sentences</td> <td>" + sentenceCount + "</td></tr>";

sentenceTable += "</table><br>";
createDiv(sentenceTable).class(tabID).parent("right");
  
  
var wordTable = "<table>";

wordTable += "<tr><td>Word Count</td> <td>" + wordCount + "</td></tr>";
wordTable += "<tr><td>Unique Word Count</td> <td>" + wordsArray.length + "</td></tr>";
wordTable += "<tr><td>Vocab Richness Ratio</td> <td>" + round(wordsArray.length/wordCount*100)/100 + "</td></tr>";
wordTable += "<tr><td>Average word length</td> <td>" + avgWordLength + "</td></tr>";
wordTable += "<tr><td>Longest word</td> <td>" + longestWord + "</td></tr>";

wordTable += "</table><br>";
createDiv(wordTable).class(tabID).parent("right");

var charsTable = "<table>";

charsTable += "<tr><td>Alphanumerical Characters</td> <td>" + charsAlphaNum + "</td></tr>";
charsTable += "<tr><td>Character Count,<br>excluding white spaces</td> <td>" + charsNoWhite + "</td></tr>";
charsTable += "<tr><td>Character Count,<br>including white spaces</td> <td>" + (charsNoWhite + tokens.length - sentences.length) + "</td></tr>";

charsTable += "</table>";
createDiv(charsTable).class(tabID).parent("right");

 
  tabNumber += 1;
}

//When new file is loaded
function gotFile(file) {
  createDiv("<h1>"+file.name+"</h1>").class(tabNumber).parent("left");

  // Handle image and text differently
  if (file.type === 'image') {
    createImg(file.data);
  } 
  else if (file.type === 'text') {
    tabs[file.name] = new Tab(file.name, tabNumber);
    switchTab(file.name, tabNumber);
    analyzeText(file, tabNumber);
  }
}

//Creates new tab
function Tab(name, number)
{
  //Creates button for new tab
  var newButton = createButton("<h1>Document " + tabNumber + "</h1>").parent('bottom');
  newButton.mouseClicked(hit);
  
  //When button is hit
  function hit()
  {
    //switches to tab
    switchTab(name, number);
  }
  
}

//switches to tab
function switchTab(name, number)
{
   
   // Declare all variables
    var i, tabcontent, selectedTab;

    //runs through tab numbers and gets all tabs
    for(var x = 0; x<tabNumber; x++)
    {
        tabcontent = document.getElementsByClassName(x);

        //Runs through tabs
        for (i = 0; i < tabcontent.length; i++) {

            //If tab numbers = tab number of button hit
            if(x == number)
            {
              tabcontent[i].style.display = "block";
            
            }

            else
            {
            tabcontent[i].style.display = "none";
            
          }
        }
    }

  


}


