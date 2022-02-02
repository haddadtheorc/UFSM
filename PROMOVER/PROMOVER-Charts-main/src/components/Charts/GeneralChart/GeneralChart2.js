import React from "react";
import Chart from "react-apexcharts";

const GeneralChart2 = (props) => {
  let data_name = props.data.map((data) => data.name);
  let data_total = props.data.map((data) => data.total);
  let data_filled = props.data.map((data) => data.filled);
  let data_unnocupied = props.data.map((data) => data.unnocupied);

  let state = {
    options: {
      colors: ["#9966ff", "#4bc0c0", "#fa2f5a"],
      chart: {
        type: "bar",
        height: 350,
        stacked: true,
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
        name: "Ofertadas",
        data: data_total,
      },
      {
        name: "Preenchidas",
        data: data_filled,
      },
      { name: "Suplentes", data: data_unnocupied },
    ],
  };

  return (
    <div id="chart">
      <center>
        <h2>1. Vagas</h2>
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

export default GeneralChart2;
