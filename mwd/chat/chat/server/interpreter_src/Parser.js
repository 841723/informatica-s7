"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.runInterpreter = void 0;
var E = require("./Expressions");
var S = require("./Scanner");
var Parser = /** @class */ (function () {
    function Parser(scanner) {
        this.scanner = scanner;
    }
    ;
    Parser.prototype.parse = function (str) {
        var tokens = this.scanner.getTokens(str);
        var finalExpression = this.startParsing(tokens);
        //console.log(finalExpression.terms[0].factors) 
        return finalExpression;
    };
    Parser.prototype.checkEmptyTokens = function (tokens) {
        if (tokens.length <= 0) {
            throw new Error("Tokens are empty");
        }
    };
    Parser.prototype.startParsing = function (tokens) {
        var exp = this.parseExpression(tokens);
        if (tokens.length > 0) {
            throw new Error("Token: '" + tokens[0].str + "' causing problem");
        }
        return exp;
    };
    Parser.prototype.parseExpression = function (tokens) {
        this.checkEmptyTokens(tokens);
        var exp = new E.Expression();
        if (tokens[0].type != S.Type.operator) {
            exp.addTerm(1, this.parseTerm(tokens));
        }
        while (tokens.length > 0 && tokens[0].type == S.Type.operator) {
            var operator = tokens[0];
            if (operator.str == "+") {
                tokens.shift();
                exp.addTerm(1, this.parseTerm(tokens));
            }
            else if (operator.str == "-") {
                tokens.shift();
                exp.addTerm(-1, this.parseTerm(tokens));
            }
            else {
                break;
            }
        }
        return exp;
    };
    Parser.prototype.parseTerm = function (tokens) {
        this.checkEmptyTokens(tokens);
        var term = new E.Term();
        if (tokens[0].type != S.Type.operator) {
            term.addFactor("*", this.parseFactor(tokens));
        }
        while (tokens.length > 0 && tokens[0].type == S.Type.operator) {
            var operator = tokens[0];
            if (operator.str == "*") {
                tokens.shift();
                term.addFactor("*", this.parseFactor(tokens));
            }
            else if (operator.str == "/") {
                tokens.shift();
                term.addFactor("/", this.parseFactor(tokens));
            }
            else {
                break;
            }
        }
        if (term.isEmpty()) {
            throw new Error("Token: '" + tokens[0].str + "' causing problems");
        }
        return term;
    };
    Parser.prototype.parseFactor = function (tokens) {
        this.checkEmptyTokens(tokens);
        var factor = new E.Factor();
        switch (tokens[0].type) {
            case S.Type.openBracket:
                factor.factor = this.parseBracketedExpression(tokens);
                break;
            case S.Type.functionName:
                factor.factor = this.parseFunctionCall(tokens);
                break;
            case S.Type.num:
                factor.factor = this.parseNumber(tokens);
                break;
            default:
                throw new Error("No type for factor found at token: '" + tokens[0].str + "'");
        }
        return factor;
    };
    Parser.prototype.parseBracketedExpression = function (tokens) {
        this.checkEmptyTokens(tokens);
        var brackExpression = new E.BracketedExpression();
        //already checked for opening bracket
        tokens.shift();
        brackExpression.expression = this.parseExpression(tokens);
        this.checkEmptyTokens(tokens);
        var bracket = tokens.shift();
        if (bracket.type != S.Type.closingBracket) {
            throw new Error("Missing closing bracket");
        }
        return brackExpression;
    };
    Parser.prototype.parseFunctionCall = function (tokens) {
        this.checkEmptyTokens(tokens);
        var functionCall = new E.FunctionCall();
        //we already know there is a functioncall token
        var token = tokens.shift();
        functionCall.name = token.str;
        if (tokens.length > 0 && tokens[0].type == S.Type.openBracket) {
            tokens.shift();
            functionCall.expression = this.parseExpression(tokens);
            if (tokens.length > 0 && tokens[0].type == S.Type.closingBracket) {
                tokens.shift();
            }
            else {
                throw new Error("No closing brackets for function call");
            }
        }
        else {
            throw new Error("No opening bracket for function call");
        }
        return functionCall;
    };
    Parser.prototype.parseNumber = function (tokens) {
        var _a;
        this.checkEmptyTokens(tokens);
        var num = (_a = tokens.shift()) === null || _a === void 0 ? void 0 : _a.str;
        if (num == undefined) {
            throw new Error("No number left");
        }
        return new E.Num(num);
    };
    return Parser;
}());
var runInterpreter = function (input) {
    var parser = new Parser(new S.Scanner());
    try {
        var sol = (parser.parse(input).eval());
        console.log("sol.toString()", sol.toString());
        return sol.toString();
    }
    catch (e) {
        return e.message.toString();
    }
};
exports.runInterpreter = runInterpreter;
