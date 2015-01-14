var polyline = require('./polyline.js');
var errand = require('./errand.js');
var locals = require('./locals.js');
var constants = require('./constants.js');

module.exports = (function() {

    var changeToResultsStripe = function() {
        $('#stripe-input').css('left', -constants.menuStripeWidth);
        $('#stripe-results').css('left', 0);
    };

    var changeToInputStripe = function() {
        $('#stripe-input').css('left', 0);
        $('#stripe-results').css('left', constants.menuStripeWidth);
    };

    var createErrandBox = function() {

        //TODO: This is super hacky. I do this so I can preserve
        // the event, since I cannot call search.makeSearch(event.target.value); from here

        //Clone the events attached as well
        var newErrandBox = $('#errand-hack').clone(true);
        newErrandBox.val('');
        newErrandBox.removeAttr('id');
        newErrandBox.removeAttr('disabled');
        newErrandBox.removeClass('hidden');
        newErrandBox.addClass('errand-input');
        newErrandBox.keyup(function(event) {
            errand.makeSearch(event.target);
        });
        newErrandBox.click(function(event) {
            errand.makeSearch(event.target);
        });
        var useGtspButton = $('#b-use-gtsp').clone(true);

        var wrapper = $('<div>').append(newErrandBox).append(useGtspButton);

        $('#errands-point').append(wrapper);

    };

    var insertTextIntoNextBox = function(text) {
        var originInput = $('#origin-input-primary');
        if (originInput.val() === '') {
            originInput.val(text);
            lockOriginInput();
            return;
        }

        var errandInput = $('.errand-input').last();
        errandInput.val(text);
        disableNextErrandInput();
    };

    var lockOriginInput = function() {
        var originInput = $('#origin-input-primary');
        var errandInput = $('#errand-input-primary');

        originInput.attr('disabled', 'true');
        errandInput.removeAttr('disabled');
        errandInput.attr('placeholder', locals.searchSuggestion);
    };

    var setOriginText = function(text) {
        $('#origin-input-primary').val(text);
    };

    var disableNextErrandInput = function() {
        var errandInputs = $('.errand-input');
        for (var i = 0; i < errandInputs.length; i++) {
            if (errandInputs[i].disabled !== true) {
                errandInputs[i].disabled = true;
                if (allErrandBoxesAreFull) {
                    createErrandBox();
                }
                return;
            }
        }
    };

    var allErrandBoxesAreFull = function() {
        var errandInputs = $('.errand-input');
        for (var i = 0; i < errandInputs.length; i++) {
            if (errandInputs[i].value === '') {
                return false;
            }
        }

        return true;
    };

    var setResults = function(resultArray) {

        //Hack to avoid a double polyline at the very beginning. No idea why it is done.
        polyline.createPolyline(null);

        var i;
        var origin = resultArray.origin || '';
        var errands = resultArray.errands || [];
        var destination = resultArray.destination || '';

        var templateDiv = $('<div>', {
            class: 'direction-step'
        }).append($('<text>', {
            class: 'number'
        })).append($('<span>', {
            class: 'text'
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
        clearResults: clearResults,
        createErrandBox: createErrandBox,
        allErrandBoxesAreFull: allErrandBoxesAreFull,
        insertTextIntoNextBox: insertTextIntoNextBox,
        disableNextErrandInput: disableNextErrandInput,
        lockOriginInput: lockOriginInput,
        setOriginText: setOriginText,
    };

})();
