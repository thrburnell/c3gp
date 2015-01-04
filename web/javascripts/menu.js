module.exports = (function() {

    var stripeWidth = 225;

    var changeToResultsStripe = function() {
        $("#stripe-input").css("left", -stripeWidth);
        $("#stripe-results").css("left", 0);
    };

    var changeToInputStripe = function() {
        $("#stripe-input").css("left", 0);
        $("#stripe-results").css("left", stripeWidth);
    };

	return {
		changeToResultsStripe: changeToResultsStripe,
		changeToInputStripe: changeToInputStripe
	};

})();
