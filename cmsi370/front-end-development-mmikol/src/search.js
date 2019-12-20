(() => {
  const setupSearchEventListeners = () => {
    const searchForm = $('form.searchForm')
    const searchButton = $('#searchButton')
    const searchTerm = $('#searchTerm')

    searchForm.submit(async event => {
      event.preventDefault()

      try {
        const search = await window.ApiService.searchRecipes({
          query: searchTerm.val(),
          number: 15
        })

        displayResults(search.results)
      } catch (error) {
        $('#searchResultContainer').empty().append(
          $('<div></div>')
            .addClass('col alert alert-danger')
            .text('Sorry, but something went wrong.')
        )
      }
    })

    searchTerm.bind('input', () => searchButton.prop('disabled', !searchTerm.val()))
  }

  const resultElement = result => {
    if (result.title.length > 45) {
      return `<li>
                <a href="recipe-page.html#${result.id}">${result.title.substring(0, 45)}...</a>
              </li>`
    }
    return `<li>
              <a href="recipe-page.html#${result.id}">${result.title}</a>
            </li>`
  }

  const displayResults = results => {
    $('#searchResultContainer').show()
    $('.searchResultList').empty().append(results.map(resultElement))
  }

  const init = () => {
    setupSearchEventListeners()
  }

  window.SpoonacularSearchHandler = {
    init
  }
})()