import React from "react";
import Chart from "react-apexcharts";

const AreasChart = (props) => {
  let data_name = props.data.map((data) => data.name);

  let disciplines = {};
  props.data
    .map((data) => data.disciplines)
    .forEach((item, index) => {
      item.forEach((item, index) => {
        if (!disciplines[item.name]) {
          disciplines[item.name] = [];
        }
        disciplines[item.name].push(item.value);
      });
    });

  let state = {
    options: {
      theme: { palette: "palette2" },
      chart: {
        type: "bar",
        height: 350,
        stacked: false,
        toolbar: {
          show: true,
        },
        zoom: {
          enabled: true,
        },
      },
      responsive: [
        {
          breakpoint: 480,
          options: {
            legend: {
              position: "bottom",
              offsetX: 10,
              offsetY: 0,
            },
          },
        },
      ],
      plotOptions: {
        bar: {
          horizontal: false,
          endingShape: "rounded",
        },
      },
      xaxis: {
        type: "category",
        categories: data_name,
        labels: {
          style: {
            fontWeight: 1000,
          },
        },
      },
      legend: {
        position: "right",
        offsetY: 40,
      },
      fill: {
        opacity: 1,
      },
    },
    series: [
      {
        name: "Engenharias",
        data: disciplines.engineering,
      },
      {
        name: "Biológicas",
        data: disciplines.biology,
      },
      {
        name: "Saúde",
        data: disciplines.health,
      },
    ],
  };

  return (
    <div id="chart">
      <center>
        <h2>2.2 Disciplinas Ofertadas por Área</h2>
      </center>
      <Chart
        options={state.options}
        series={state.series}
        type="bar"
        height={500}
      />
    </div>
  );
};

export default AreasChart;
