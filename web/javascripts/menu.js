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
        var newErrandBox = $('#errand-template').clone(true);
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

        $(".gtsp-button").hide();
        var useGtspButton = $('#b-use-gtsp').clone(true);
        useGtspButton.show();

        useGtspButton.removeClass('first');

        var wrapper = $('<div>', {
            class: 'delete-on-clear'
        }).append(newErrandBox)
        .append(useGtspButton);

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

    var getOriginText = function() {
        return $('#origin-input-primary').val();
    };

    var disableNextErrandInput = function() {
        var errandInputs = $('.errand-input');
        for (var i = 0; i < errandInputs.length; i++) {
            if (errandInputs[i].disabled !== true) {
                errandInputs[i].disabled = true;

                var letter = String.fromCharCode('A'.charCodeAt(0) + (i + 1));
                var markerUrl = makeIcon(letter, constants.markerColour1, constants.markerColourLetter);

                var menuMarker = $('<div>', {
                    class: 'menu-marker'
                }).append($('<img>', {
                    src: markerUrl.url
                }));

                var errDiv = $(errandInputs[i]).parent();
                errDiv.append(menuMarker);

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

    var clearInputStripe = function() {
        var useGtspButton = $('#b-use-gtsp').show();
        $('.delete-on-clear').remove();
        $('.input-box').val('').removeAttr('disabled');
        $('.menu-marker').remove();
    };

    var setResults = function(resultArray) {

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

        $("#d-total-time").html('<b>TOTAL: ' + resultArray.totalTime + '</b>');
    };

    var clearResults = function() {
        $('#stripe-results').find('.direction-step').not('.hidden').remove();
    };

    var makeIcon = function(letter, colour, letterColour) {
        return new google.maps.MarkerImage("http://chart.apis.google.com" +
               "/chart?chst=d_map_pin_letter&chld=" + letter + "|" +
               colour + "|" + letterColour);
    };

    return {
        changeToResultsStripe: changeToResultsStripe,
        changeToInputStripe: changeToInputStripe,
        setResults: setResults,
        clearResults: clearResults,
        clearInputStripe: clearInputStripe,
        createErrandBox: createErrandBox,
        allErrandBoxesAreFull: allErrandBoxesAreFull,
        insertTextIntoNextBox: insertTextIntoNextBox,
        disableNextErrandInput: disableNextErrandInput,
        lockOriginInput: lockOriginInput,
        setOriginText: setOriginText,
        getOriginText: getOriginText,
    };

})();
