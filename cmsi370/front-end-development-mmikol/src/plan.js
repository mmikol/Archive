(() => {
  const setupPlanEventListeners = () => {
    const randomForm = $('form.randomForm')

    randomForm.submit(async event => {
      event.preventDefault()

      try {
        const plan = await window.ApiService.createMealPlan({ timeFrame: 'week' })
        displayPlan(plan.items)
      } catch (error) {
        $('#mealPlanTable').empty().append(
          $('<div></div>')
            .addClass('col alert alert-danger')
            .text('Sorry, but something went wrong.')
        )
      }
    })
  }

  const displayPlan = (items) => {
    $('#diceContainer').hide()
    $('#diceLabel').hide()
    $('#dayLabels').show()

    for (let i = 0; i < 21; i += 3) {
      let [bfast, lun, din] = [JSON.parse(items[i].value), JSON.parse(items[i + 1].value), JSON.parse(items[i + 2].value)]
      $('#dayMeals').append(
        `<td>
          <p>
            <span class=boldedText>breakfast:</span> 
            <a href="recipe-page.html#${bfast.id}">${bfast.title.substring(0, 35)}...</a>
          </p>
          <p>
            <span class=boldedText>lunch:</span> 
            <a href="recipe-page.html#${lun.id}">${lun.title.substring(0, 35)}...</a>
          </p>
          <p>
            <span class=boldedText>dinner:</span> 
            <a href="recipe-page.html#${din.id}">${din.title.substring(0, 35)}...</a>
          </p>
        </td>`
      )
    }
  }

  const init = () => {
    setupPlanEventListeners()
  }

  window.SpoonacularPlanHandler = {
    init
  }
})()