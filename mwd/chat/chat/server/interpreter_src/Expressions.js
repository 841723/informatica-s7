"use strict";
var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
Object.defineProperty(exports, "__esModule", { value: true });
exports.BracketedExpression = exports.FunctionCall = exports.Factor = exports.Term = exports.Expression = exports.Num = void 0;
//interface/record for functions
var functions = {
    "sin": Math.sin,
    "cos": Math.cos,
    "tan": Math.tan,
    "custom": function (x) { return x * 3; }
};
//Treenode is the superclass for the AST structure
var TreeNode = /** @class */ (function () {
    function TreeNode() {
    }
    return TreeNode;
}());
/**
 * Number class
 */
var Num = /** @class */ (function (_super) {
    __extends(Num, _super);
    function Num(str) {
        var _this = _super.call(this) || this;
        _this.digits = str;
        return _this;
    }
    ;
    Num.prototype.eval = function () {
        return Number(this.digits);
    };
    return Num;
}(TreeNode));
exports.Num = Num;
/**
 * Expression class
 */
var Expression = /** @class */ (function (_super) {
    __extends(Expression, _super);
    function Expression() {
        var _this = _super.call(this) || this;
        //tuple of (operator(-1,+1), term)
        _this.terms = [];
        return _this;
    }
    ;
    Expression.prototype.addTerm = function (operator, term) {
        this.terms.push([operator, term]);
    };
    Expression.prototype.eval = function () {
        var final_value = 0;
        this.terms.forEach(function (value) {
            var operator = value[0];
            var term = value[1];
            final_value += operator * term.eval();
        });
        return final_value;
    };
    return Expression;
}(TreeNode));
exports.Expression = Expression;
/**
 * Term class
 */
var Term = /** @class */ (function (_super) {
    __extends(Term, _super);
    function Term() {
        var _this = _super.call(this) || this;
        //list of operators ("*","/") and factors
        _this.factors = [];
        return _this;
    }
    Term.prototype.addFactor = function (operator, factor) {
        this.factors.push([operator, factor]);
    };
    Term.prototype.eval = function () {
        var final_value = this.factors[0][1].eval();
        for (var i = 0; i < this.factors.length - 1; i++) {
            if (this.factors[i + 1][0] == "*") {
                final_value *= this.factors[i + 1][1].eval();
            }
            else {
                final_value /= this.factors[i + 1][1].eval();
            }
        }
        return final_value;
    };
    Term.prototype.isEmpty = function () {
        return this.factors.length <= 0;
    };
    return Term;
}(TreeNode));
exports.Term = Term;
/**
 * Factor class
 */
var Factor = /** @class */ (function (_super) {
    __extends(Factor, _super);
    function Factor() {
        return _super.call(this) || this;
    }
    ;
    Factor.prototype.eval = function () {
        return this.factor.eval();
    };
    return Factor;
}(TreeNode));
exports.Factor = Factor;
/**
 * Function call class
 */
var FunctionCall = /** @class */ (function (_super) {
    __extends(FunctionCall, _super);
    function FunctionCall() {
        return _super.call(this) || this;
    }
    ;
    FunctionCall.prototype.eval = function () {
        if (functions[this.name] == undefined) {
            throw new Error("Function name '" + this.name + "' not found");
        }
        return functions[this.name](this.expression.eval());
    };
    return FunctionCall;
}(TreeNode));
exports.FunctionCall = FunctionCall;
/**
 * Bracketed Expression class
 */
var BracketedExpression = /** @class */ (function (_super) {
    __extends(BracketedExpression, _super);
    function BracketedExpression() {
        return _super.call(this) || this;
    }
    ;
    BracketedExpression.prototype.eval = function () {
        return this.expression.eval();
    };
    return BracketedExpression;
}(TreeNode));
exports.BracketedExpression = BracketedExpression;
