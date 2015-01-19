var errands = require('./errands.json');
var locals = require('./locals.js');

module.exports = (function() {

    var fuzzyOptions = {
            keys: ['colloquial', 'search_keywords'],
            id: 'colloquial',
            threshold: 0.2
    };

    var fuzzy = new Fuse(errands, fuzzyOptions);

    var makeSearch = function(box) {
        box = $(box);
        var inputField = jQuery.trim(box.val());
        var results;

        if (inputField.length === 0) {
            results = fuzzy.search(' ');
        } else {
            results = fuzzy.search(inputField);
        }

        if (inputField.length > 0) {
            results.push(locals.searchFor + ' "' + inputField + '"');
        }

        box.autocomplete({
            source: function(request, response) {
                response(results);
            },
            select: function(event, ui) {
                var query = ui.item.value;
                var errandForQuery = jQuery.grep(errands, function(errand) {
                    return errand.colloquial === query;
                });

                if (errandForQuery.length === 0) {
                } else if (errandForQuery.length === 1) {
                    event.target.title = errandForQuery[0].api_id;
                    event.target.colloquial = errandForQuery[0].colloquial;
                } else {
                    console.error("There is an issue with searching for errands");
                }

                var hitEnterEvent = jQuery.Event('keyup');
                hitEnterEvent.which = 13; // Equivalent to pressing enter
                $(event.target).trigger(hitEnterEvent);
            },
            minLength: 0
        });
    };

    return {
        makeSearch: makeSearch
    };

})();
