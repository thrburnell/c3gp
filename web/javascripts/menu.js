var polyline = require('./polyline.js');

module.exports = (function() {

    var stripeWidth = 225;

    var changeToResultsStripe = function() {
        $('#stripe-input').css('left', -stripeWidth);
        $('#stripe-results').css('left', 0);
    };

    var changeToInputStripe = function() {
        $('#stripe-input').css('left', 0);
        $('#stripe-results').css('left', stripeWidth);
    };

    var setResults = function(resultArray) {

        //Hack to avoid a double polyline at the very beginning. No idea why it is done.
        polyline.createPolyline(null);

        var i;
        var origin = resultArray.origin || '';
        var errands = resultArray.errands || [];
        var destination = resultArray.destination || '';

        var templateDiv = $("<div>", {
            class: "direction-step"
        }).append($("<text>", {
            class: "number"
        })).append($("<span>", {
            class: "text"
        }));

        var originDiv = templateDiv.clone();
        originDiv.find('text').html(1);
        originDiv.find('span').html(origin);
        $('#result-origin').append(originDiv);

        var divErrands = $('#result-errands');

        errands.forEach(function(errand, index) {
            var newStep = templateDiv.clone();
            newStep.find('text').html(index + 2);
            newStep.find('span').html(errand);
            newStep.hover(function() {
                polyline.highlightSegment(index);
            }, function() {
                polyline.normalizeSegment(index);
            });
            divErrands.append(newStep);
        });

        var destinationDiv = templateDiv.clone();
        destinationDiv.find('text').html(errands.length + 2);
        destinationDiv.find('span').html(destination);
        destinationDiv.hover(function() {
            polyline.highlightSegment(errands.length);
        }, function() {
            polyline.normalizeSegment(errands.length);
        });
        $('#result-destination').append(destinationDiv);
    };

    var clearResults = function() {
        $('#stripe-results').find('.direction-step').not('.hidden').remove();
    };

    return {
        changeToResultsStripe: changeToResultsStripe,
        changeToInputStripe: changeToInputStripe,
        setResults: setResults,
        clearResults: clearResults
    };

})();
