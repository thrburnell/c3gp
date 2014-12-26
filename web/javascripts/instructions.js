module.exports = (function() {

    var defaultMessage = 'Select points of interest';
    var deleteOriginErrorMessage = 'Cannot delete starting position!';

    var setInstruction = function(message) {
        $("#instructions").text(message);
    };

    return {
        defaultMessage: function() {
            return setInstruction(defaultMessage);
        },
        originError: function() {
            return setInstruction(deleteOriginErrorMessage);
        }
    };

})();
