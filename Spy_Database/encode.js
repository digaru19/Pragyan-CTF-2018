
function encodeForm(e) {

    var spy_name = document.getElementById("spy_name");

    console.log(spy_name.value);
    var encoded = btoa(spy_name.value);
    spy_name.value = encoded;
    console.log(spy_name.value);
    return true;
}

var form = document.getElementById('search_form');

if (form.attachEvent) {
    form.attachEvent("submit", encodeForm);
} else {
    form.addEventListener("submit", encodeForm);
}

document.getElementById("spy_name").value = "";
