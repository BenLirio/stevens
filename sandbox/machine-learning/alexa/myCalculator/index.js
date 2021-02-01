'use strict';

//import ask-sdk-core
const Alexa = require('ask-sdk-core');

//skill name
const appName = 'My Calculator';

//code for the handlers
const LaunchRequestHandler = {
    canHandle(handlerInput) {
        return handlerInput.requestEnvelope.request.type === 'LaunchRequest';
    },
    handle(handlerInput) {
        //welcome message
        let speechText = 'Welcome to my Calculator, you can say add 2 and 5 or multiply 4 and 12';
        //welcome screen message
        let displayText = "Welcome to my calculator"
        return handlerInput.responseBuilder
            .speak(speechText)
            .reprompt(speechText)
            .withSimpleCard(appName, displayText)
            .getResponse();
    }
};

//implement custom handlers


//end Custom handlers

const HelpIntentHandler = {
    canHandle(handlerInput) {
        return handlerInput.requestEnvelope.request.type === 'IntentRequest'
            && handlerInput.requestEnvelope.request.intent.name === 'AMAZON.HelpIntent';
    },
    handle(handlerInput) {
        //help text for your skill
        let speechText = 'You can say add 3 and 5 or subtract 3 and 2';

        return handlerInput.responseBuilder
            .speak(speechText)
            .reprompt(speechText)
            .withSimpleCard(appName, speechText)
            .getResponse();
    }
};

const CancelAndStopIntentHandler = {
    canHandle(handlerInput) {
        return handlerInput.requestEnvelope.request.type === 'IntentRequest'
            && (handlerInput.requestEnvelope.request.intent.name === 'AMAZON.CancelIntent'
                || handlerInput.requestEnvelope.request.intent.name === 'AMAZON.StopIntent');
    },
    handle(handlerInput) {
        let speechText = 'Goodbye';
        return handlerInput.responseBuilder
            .speak(speechText)
            .withSimpleCard(appName, speechText)
            .getResponse();
    }
};

const SessionEndedRequestHandler = {
    canHandle(handlerInput) {
        return handlerInput.requestEnvelope.request.type === 'SessionEndedRequest';
    },
    handle(handlerInput) {
        //any cleanup logic goes here
        return handlerInput.responseBuilder.getResponse();
    }
};

const AddIntentHandler = {
	canHandle(handlerInput) {
		return handlerInput.requestEnvelope.request.type === 'IntentRequest'
		&& handlerInput.requestEnvelope.request.intent.name === 'AddIntent'
	},
	handle(handlerInput) {
		let speachText = '';
		let displayText = '';
		let intent = handlerInput.requestEnvelope.request.intent;
		let firstNumber = intnet.slots.firstNumber.value;
		let secondNumber = intnet.slots.secondNumber.value;
		if (firstNumber && seondNumber) {
			let result = parseInt(firstNumber) + parseInt(secondNumber);
			speachText = `The result of ${firstNumber} plus ${secondNumber} is ${result}`
			displayText = `${result}`
			return handlerInput.responseBuilder
			.speak(speachText)
			.withSimpleCard(appName, displayText)
			.withShouldEndSession(true)
			.getResponse();
		} else {
			return handlerInput.responseBuilder
			.addDelegateDirective(intent)
			.getResponse();
		}
	}
};

const SubtractIntentHandler = {
	canHandle(handlerInput) {
		return handelrInput.requestEnvolope.request.intent.type === 'IntentRequest'
		&& heanlderInput.requestEnvolope.request.intent.name === 'SubtractIntent'
	},
	handle(handlerInput) {
		let displayText = ''
		let speachText = ''
		let intent = handlerInput.requestEnvolope.request.intent
		let firstNumber = intent.slots.firstNumber.value
		let secondNumber = intent.slots.secondNumber.value
		if (firstNumber && secondNumber) {
			let result = parseInt(firstNumber) - parseInt(secondNumber)
			speachText = `The result of ${firstNumber} minus ${secondNumber} is ${result}`
			displayText = `${result}`
			return handlerInput.responseBuilder
			.speak(speachText)
			.withSimpleCard(appName, displayText)
			.withShouldEndSession(true)
			.getResponse();
		} else {
			return heandlerInput.requestBuilder
			.addDelegateDirective(intent)
			.getResponse();
		}
	}

};

//Lambda handler function
//Remember to add custom request handlers here
exports.handler = Alexa.SkillBuilders.custom()
     .addRequestHandlers(LaunchRequestHandler,
                         HelpIntentHandler,
                         CancelAndStopIntentHandler,
                         SessionEndedRequestHandler,
			 AddIntentHandler).lambda();
