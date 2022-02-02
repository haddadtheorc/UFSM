import React from "react";
import Chart from "react-apexcharts";

const GeneralChart = (props) => {
  let data_name = props.data.map((data) => data.name);
  let data_total = props.data.map((data) => data.total);
  let data_filled = props.data.map((data) => data.filled);
  let data_approved = props.data.map((data) => data.approved);
  let data_reproved = props.data.map((data) => data.reproved);
  let data_dropouts = props.data.map((data) => data.dropouts);
  let data_unnocupied = props.data.map((data) => data.unnocupied);

  let state = {
    options: {
      colors: ["#9966ff", "#4bc0c0", "#6e7075", "#1a98ed", "#fa2f5a"],
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
        name: "Ofertadas",
        data: data_total,
      },
      {
        name: "Preenchidas",
        data: data_filled,
      },
      { name: "Suplentes", data: data_unnocupied },
      {
        name: "Aprovações",
        data: data_approved,
      },
      {
        name: "Reprovações",
        data: data_reproved,
      },
      { name: "Desistências", data: data_dropouts },
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

export default GeneralChart;
